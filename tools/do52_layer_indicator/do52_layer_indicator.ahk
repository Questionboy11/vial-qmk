#Requires AutoHotkey v2.0
#SingleInstance Force
Persistent

; DO52 レイヤー表示
; キーボードのファームウェアは状態が変わると F13〜F21 を送ります。
;   F13 基本 / F14 記号（1文字） / F15 記号（固定） / F16 ナビ・テンキー / F17 ゲーム
;   F18 / F19 マウス開始 / 終了    F20 / F21 Caps Word オン / オフ
; このスクリプトはそれを受け取り（アプリには渡しません）、画面端のミニ配置図を更新します。

SETTINGS_FILE := A_ScriptDir "\settings.ini"
LAYOUT_FILE   := A_ScriptDir "\layout.txt"
STARTUP_LINK  := A_Startup "\DO52 Layer Indicator.lnk"
KEY_COUNT     := 66

MENU_STARTUP := "Windows の起動時に自動で起動"
MENU_RESET   := "表示位置を初期位置に戻す"
MENU_BASE    := "表示を「基本」に戻す"
MENU_RELOAD  := "配置ファイルを再読み込み"
MENU_EXIT    := "終了"

LAYERS := Map(
    "base", {name: "基本",           section: "base", accent: "3A3A3A"},
    "sym1", {name: "記号（1文字）",  section: "sym",  accent: "8C5A1A"},
    "symL", {name: "記号（固定）",   section: "sym",  accent: "C0661A"},
    "nav",  {name: "ナビ・テンキー", section: "nav",  accent: "1F4E79"},
    "game", {name: "ゲーム",         section: "game", accent: "7A2626"},
)

COLOR_WINDOW       := "1E1E1E"
COLOR_INHERIT      := "2C2C2C"
COLOR_INHERIT_TEXT := "777777"
COLOR_EMPTY        := "242424"
COLOR_MOUSE        := "2E7D32"
COLOR_CAPS         := "6A1B9A"
COLOR_IME_ON       := "B71C1C"
COLOR_IME_OFF      := "455A64"

cfg := {
    unit:        Integer(IniRead(SETTINGS_FILE, "display", "unit", 28)),
    alphaIdle:   Integer(IniRead(SETTINGS_FILE, "display", "alpha_idle", 255)),
    alphaActive: Integer(IniRead(SETTINGS_FILE, "display", "alpha_active", 255)),
    flashMs:     Integer(IniRead(SETTINGS_FILE, "display", "flash_ms", 1000)),
}

state := {layer: "base", mouse: false, caps: false, ime: -1}

try {
    layout := LoadLayout(LAYOUT_FILE)
} catch as err {
    MsgBox("配置ファイルを読み込めませんでした。`n`n" err.Message, "DO52 レイヤー表示", "Icon!")
    ExitApp()
}

ui := BuildWindow()
BuildTrayMenu()
Render()
ShowWindow()
OnMessage(0x0201, OnLButtonDown)   ; WM_LBUTTONDOWN
OnMessage(0x0232, OnExitSizeMove)  ; WM_EXITSIZEMOVE
SetTimer(PollIme, 250)

; ---------------------------------------------------------------------------
; 配置ファイル

LoadLayout(path) {
    layers := Map()
    current := ""
    for line in StrSplit(FileRead(path, "UTF-8"), "`n", "`r") {
        line := Trim(line)
        if (line = "" || SubStr(line, 1, 1) = ";")
            continue
        if RegExMatch(line, "^\[(\w+)\]$", &m) {
            current := m[1]
            layers[current] := []
            continue
        }
        if (current = "")
            continue
        for token in StrSplit(RegExReplace(line, "\s+", " "), " ")
            if (token != "")
                layers[current].Push(token)
    }
    for name in ["base", "sym", "nav", "mouse", "game"] {
        if !layers.Has(name)
            throw Error("[" name "] がありません。")
        if (layers[name].Length != KEY_COUNT)
            throw Error("[" name "] のキー数が " layers[name].Length " 個です（" KEY_COUNT " 個必要）。")
    }
    return layers
}

; LAYOUT の順（4 段 × 12、親指 8、スティック 10）に、各キーの位置と大きさを単位 u で返す
KeyGeometry() {
    keys := []
    leftY  := [0.75, 0.5, 0.25, 0, 0.25, 0.5]
    rightY := [0.5, 0.25, 0, 0.25, 0.5, 0.75]
    loop 4 {
        row := A_Index - 1
        loop 6
            keys.Push({x: A_Index - 1, y: leftY[A_Index] + row, w: 1, h: 1})
        loop 6
            keys.Push({x: A_Index + 9, y: rightY[A_Index] + row, w: 1, h: 1})
    }
    for pos in [[0, 5], [1, 4.75], [4, 4.5], [5, 4.75], [10, 4.75], [11, 4.5], [14, 4.75], [15, 5]]
        keys.Push({x: pos[1], y: pos[2], w: 1, h: 1})
    s := 0.6
    for cx in [7.0, 9.0]
        for d in [[0, -1], [-1, 0], [0, 0], [1, 0], [0, 1]]
            keys.Push({x: cx + d[1] * s - s / 2, y: 5.0 + d[2] * s - s / 2, w: s, h: s, small: true})
    return keys
}

; ---------------------------------------------------------------------------
; ウィンドウ

; Text の 0x280 = SS_CENTERIMAGE（上下中央）| SS_NOPREFIX（& をそのまま表示）
BuildWindow() {
    u := cfg.unit
    pad := 6
    header := Round(u * 0.8)
    width := 16 * u + pad * 2
    height := header + 6 * u + pad * 2
    fontSize := Max(6, Round(u / 4))

    g := Gui("+AlwaysOnTop -Caption +ToolWindow +E0x08000000", "DO52 Layer Indicator")
    g.BackColor := COLOR_WINDOW
    g.MarginX := 0, g.MarginY := 0

    g.SetFont("s" fontSize " bold", "Meiryo UI")
    nameCtrl := g.Add("Text", Format("x{} y{} w{} h{} 0x280 Center cFFFFFF", pad, 3, Round(u * 4), header - 4), "")

    badgeW := Round(u * 1.6)
    x := width - pad
    x -= u
    imeCtrl := g.Add("Text", Format("x{} y{} w{} h{} 0x280 Center cFFFFFF", x, 3, u, header - 4), "")
    x -= badgeW + 4
    capsCtrl := g.Add("Text", Format("x{} y{} w{} h{} 0x280 Center cFFFFFF Background{}", x, 3, badgeW, header - 4, COLOR_CAPS), "CAPS")
    x -= badgeW + 4
    mouseCtrl := g.Add("Text", Format("x{} y{} w{} h{} 0x280 Center cFFFFFF Background{}", x, 3, badgeW, header - 4, COLOR_MOUSE), "マウス")

    g.SetFont("s" fontSize " norm", "Meiryo UI")
    keyCtrls := []
    for k in KeyGeometry() {
        if k.HasProp("small")
            g.SetFont("s" Max(5, fontSize - 1))
        opts := Format("x{} y{} w{} h{} 0x280 Center", pad + Round(k.x * u) + 1, pad + header + Round(k.y * u) + 1, Round(k.w * u) - 2, Round(k.h * u) - 2)
        keyCtrls.Push(g.Add("Text", opts, ""))
        if k.HasProp("small")
            g.SetFont("s" fontSize)
    }

    return {gui: g, width: width, height: height, name: nameCtrl, ime: imeCtrl, caps: capsCtrl, mouse: mouseCtrl, keys: keyCtrls}
}

ShowWindow() {
    g := ui.gui
    g.Show(Format("w{} h{} Hide", ui.width, ui.height))
    WinGetPos(, , &w, &h, g)
    x := IniRead(SETTINGS_FILE, "window", "x", "")
    y := IniRead(SETTINGS_FILE, "window", "y", "")
    if (x = "" || y = "" || !IsOnScreen(Integer(x), Integer(y), w, h)) {
        MonitorGetWorkArea(MonitorGetPrimary(), , , &right, &bottom)
        x := right - w - 10
        y := bottom - h - 10
    }
    g.Show(Format("x{} y{} NoActivate", x, y))
    WinSetTransparent(cfg.alphaIdle, g)
}

IsOnScreen(x, y, w, h) {
    vx := SysGet(76), vy := SysGet(77), vw := SysGet(78), vh := SysGet(79)
    return x >= vx && y >= vy && x + w <= vx + vw && y + h <= vy + vh
}

Render() {
    info := LAYERS[state.layer]
    keys := layout[info.section]
    base := layout["base"]
    mouse := layout["mouse"]

    loop KEY_COUNT {
        legend := keys[A_Index]
        bg := info.accent
        fg := "FFFFFF"
        if (state.mouse && mouse[A_Index] != "▽") {
            legend := mouse[A_Index]
            bg := COLOR_MOUSE
        } else if (legend = "▽") {
            legend := base[A_Index]
            bg := COLOR_INHERIT
            fg := COLOR_INHERIT_TEXT
        }
        if (legend = "--") {
            legend := ""
            bg := COLOR_EMPTY
        }
        ctrl := ui.keys[A_Index]
        ctrl.Opt("+Background" bg)
        ctrl.SetFont("c" fg)
        ctrl.Value := legend
    }

    ui.name.Opt("+Background" info.accent)
    ui.name.Value := info.name
    ui.mouse.Visible := state.mouse
    ui.caps.Visible := state.caps
    ui.ime.Visible := state.ime >= 0
    if (state.ime >= 0) {
        ui.ime.Opt("+Background" (state.ime ? COLOR_IME_ON : COLOR_IME_OFF))
        ui.ime.Value := state.ime ? "あ" : "A"
    }
}

Flash() {
    WinSetTransparent(cfg.alphaActive, ui.gui)
    SetTimer(Fade, -cfg.flashMs)
}

Fade() {
    WinSetTransparent(cfg.alphaIdle, ui.gui)
}

OnLButtonDown(wParam, lParam, msg, hwnd) {
    if (hwnd = ui.gui.Hwnd || DllCall("GetAncestor", "Ptr", hwnd, "UInt", 2, "Ptr") = ui.gui.Hwnd)
        PostMessage(0x00A1, 2, 0, , ui.gui)  ; WM_NCLBUTTONDOWN / HTCAPTION
}

OnExitSizeMove(wParam, lParam, msg, hwnd) {
    if (hwnd != ui.gui.Hwnd)
        return
    WinGetPos(&x, &y, , , ui.gui)
    IniWrite(x, SETTINGS_FILE, "window", "x")
    IniWrite(y, SETTINGS_FILE, "window", "y")
}

; ---------------------------------------------------------------------------
; 状態の更新

SetLayer(name) {
    if (state.layer = name)
        return
    state.layer := name
    Render()
    Flash()
}

SetMouse(on) {
    if (state.mouse = on)
        return
    state.mouse := on
    Render()
}

SetCaps(on) {
    if (state.caps = on)
        return
    state.caps := on
    Render()
    Flash()
}

PollIme() {
    ime := GetImeOpenStatus()
    if (ime = state.ime)
        return
    state.ime := ime
    Render()
    if (ime >= 0)
        Flash()
}

; 1 = IME オン（あ）、0 = オフ（A）、-1 = 取得できない
GetImeOpenStatus() {
    hwnd := WinExist("A")
    if !hwnd
        return -1
    size := 8 + 6 * A_PtrSize + 16
    gti := Buffer(size, 0)
    NumPut("UInt", size, gti)
    if DllCall("GetGUIThreadInfo", "UInt", 0, "Ptr", gti) {
        focus := NumGet(gti, 8 + A_PtrSize, "Ptr")
        if focus
            hwnd := focus
    }
    imeWnd := DllCall("imm32\ImmGetDefaultIMEWnd", "Ptr", hwnd, "Ptr")
    if !imeWnd
        return -1
    result := 0
    ; WM_IME_CONTROL / IMC_GETOPENSTATUS, SMTO_ABORTIFHUNG
    if !DllCall("SendMessageTimeoutW", "Ptr", imeWnd, "UInt", 0x0283, "Ptr", 0x0005, "Ptr", 0, "UInt", 0x0002, "UInt", 200, "Ptr*", &result)
        return -1
    return result ? 1 : 0
}

; ---------------------------------------------------------------------------
; タスクトレイ

BuildTrayMenu() {
    tray := A_TrayMenu
    tray.Delete()
    tray.Add(MENU_STARTUP, ToggleStartup)
    tray.Add(MENU_RESET, ResetPosition)
    tray.Add(MENU_BASE, (*) => SetLayer("base"))
    tray.Add(MENU_RELOAD, (*) => Reload())
    tray.Add()
    tray.Add(MENU_EXIT, (*) => ExitApp())
    if FileExist(STARTUP_LINK)
        tray.Check(MENU_STARTUP)
    A_IconTip := "DO52 レイヤー表示"
}

ToggleStartup(*) {
    if FileExist(STARTUP_LINK) {
        FileDelete(STARTUP_LINK)
        A_TrayMenu.Uncheck(MENU_STARTUP)
    } else {
        FileCreateShortcut(A_AhkPath, STARTUP_LINK, A_ScriptDir, '"' A_ScriptFullPath '"', "DO52 レイヤー表示")
        A_TrayMenu.Check(MENU_STARTUP)
    }
}

ResetPosition(*) {
    try IniDelete(SETTINGS_FILE, "window")
    ShowWindow()
}

; ---------------------------------------------------------------------------
; キーボードからの通知（アプリには渡さない）

*F13::SetLayer("base")
*F14::SetLayer("sym1")
*F15::SetLayer("symL")
*F16::SetLayer("nav")
*F17::SetLayer("game")
*F18::SetMouse(true)
*F19::SetMouse(false)
*F20::SetCaps(true)
*F21::SetCaps(false)
