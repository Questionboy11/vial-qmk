MCU = atmega32u4
BOOTLOADER = caterina

# Bootmagic Lite（パネルを開けずにキー長押しで復旧可能にする）
BOOTMAGIC_ENABLE = lite

# ポインティングデバイス（トラックポイント）
POINTING_DEVICE_ENABLE = yes

# Vial / VIA 有効化
VIA_ENABLE = yes
VIAL_ENABLE = yes

# リンク時最適化（容量削減）
LTO_ENABLE = yes

# メモリ節約（32KB制限対策）
QMK_SETTINGS = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
MUSIC_ENABLE = no
AUDIO_ENABLE = no
COMBO_ENABLE = no
TAP_DANCE_ENABLE = no
AUTO_SHIFT_ENABLE = no
CAPS_WORD_ENABLE = no
KEY_OVERRIDE_ENABLE = no
REPEAT_KEY_ENABLE = no
LAYER_LOCK_ENABLE = no
LEADER_KEY_ENABLE = no