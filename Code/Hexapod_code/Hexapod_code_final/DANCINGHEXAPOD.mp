Project:      DANCINGHEXAPOD
Build Number: 14
Date:         Sun Nov 18 20:20:26 2012
Compiler:     ICCAVR
Version:      7.22C

NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   00E4   0019 =     25. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       00E4  __idata_start
       00FD  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   00FE   19D6 =   6614. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       007F  __start
       007F  __text_start
       00A1  _exit
       00A2  _buzzer_on
       00A4  _buzzer_off
       00A8  _delay_25ms
       00B7  _delay_xms
       00D2  _delay_50ms
       00E1  _delay_100ms
       00F0  _delay_250ms
       00FF  _delay_500ms
       010E  _delay_1s
       011D  _reset_SP_LEFT
       0123  _set_SP_LEFT
       0129  _reset_1A
       012D  _set_1A
       012F  _reset_1B
       0135  _set_1B
       013B  _reset_1C
       013F  _set_1C
       0141  _reset_2A
       0147  _set_2A
       014D  _reset_2B
       0151  _set_2B
       0153  _reset_2C
       0159  _set_2C
       015F  _reset_3A
       0165  _set_3A
       016B  _reset_3B
       0171  _set_3B
       0177  _reset_3C
       017D  _set_3C
       0183  _reset_SP_RIGHT
       0189  _set_SP_RIGHT
       018F  _reset_4A
       0193  _set_4A
       0195  _reset_4B
       0199  _set_4B
       019B  _reset_4C
       019F  _set_4C
       01A1  _reset_5A
       01A7  _set_5A
       01AD  _reset_5B
       01B3  _set_5B
       01B9  _reset_5C
       01BF  _set_5C
       01C5  _reset_6A
       01CB  _set_6A
       01D1  _reset_6B
       01D7  _set_6B
       01DD  _reset_6C
       01E3  _set_6C
       01E9  _port_init
       0211  _timer1_init
       0238  _timer1_compa_isr
       0283  _timer1_compb_isr
       02CE  _timer1_compc_isr
       0319  _timer1_ovf_isr
       0475  _uart0_init
       0486  _init_devices
       04AD  _angle_value_calculation
       04C7  _angle_1A
       04D6  _angle_1B
       04EB  _angle_1C
       0500  _angle_2A
       050F  _angle_2B
       0524  _angle_2C
       0539  _angle_3A
       0548  _angle_3B
       0565  _angle_3C
       057A  _angle_4A
       0589  _angle_4B
       05AA  _angle_4C
       05C5  _angle_5A
       05D4  _angle_5B
       05EF  _angle_5C
       060A  _angle_6A
       0619  _angle_6B
       063A  _angle_6C
       0655  _angle_135
       0675  _angle_246
       0695  _angle_all
       06A6  _servo_calibration
       06CA  _servo_on
       06CC  _servo_off
       06D0  _uart0_rx_isr
       0703  _processCommand
       0741  _main
       077F  _getStage
       0782  _setStage
       0785  _stand
       07DF  _step_up
       07F2  _step_up_slow
       0805  _step_up_zhigzhig
       0835  _step_down
       0848  _step16
       0885  _step25
       08C2  _step34
       08FF  _danceMove_HANDS_AIR
       0937  _slow_step_down
       095F  _legs246_up_left
       0981  _danceMove_SlowTripod
       0A97  _danceMove_RobotVibrate
       0AEB  _danceMove_circularRaise
       0B39  _danceMove_zhigzhigRise
       0BC0  _danceMove_ZHIGZHIG
       0BFA  _danceMove_KICK
       0C42  _finale
       0CB7  _performDanceMove
       0CD8  _performDanceMoveTime
       0CE5  _cancelMove
       0CEA  mod16u
       0CEC  div16u
       0CED  xdiv16u
       0D06  empy16s
       0D16  pop_xgset00FC
       0D1D  push_xgsetF0FC
       0D1F  push_xgset30FC
       0D21  push_xgset00FC
       0D23  push_xgset003C
       0D28  push_xgset300C
       0D2D  pop_xgset300C
       0D32  push_xgsetF000
       0D37  pop_xgsetF000
       0D3C  push_xgsetF00C
       0D43  pop_xgsetF00C
       0D4A  push_xgset303C
       0D51  pop_xgset303C
       0D58  push_xgsetF03C
       0D61  pop_xgsetF03C
       0D6A  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0200   0019 =     25. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0200  _arm_number
       0200  __data_start
       0201  _angle_upper_byte
       0202  _angle_lower_byte
       0203  _degree
       0204  _delay_count
       0206  _serial_communication_interval
       0208  _serial_communication_channel_number
       0209  _error_3B
       020B  _error_4B
       020D  _error_6B
       020F  _i
       0211  _currentMove
       0212  _previousCmd
       0213  _toggle
       0214  _motion_busy
       0215  _STAND_A
       0216  _STAND_B
       0217  _STAND_C
       0218  _stage
       0219  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0219   007B =    123. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0219  __bss_start
       0219  _write_index
       021B  _read_index
       021D  _recv_buffer
       024F  _remote_data
       0257  _angle_lower_byte_6C
       0259  _angle_upper_byte_6C
       025B  _angle_lower_byte_6B
       025D  _angle_upper_byte_6B
       025F  _angle_lower_byte_6A
       0260  _angle_upper_byte_6A
       0261  _angle_lower_byte_5C
       0263  _angle_upper_byte_5C
       0265  _angle_lower_byte_5B
       0267  _angle_upper_byte_5B
       0269  _angle_lower_byte_5A
       026A  _angle_upper_byte_5A
       026B  _angle_lower_byte_4C
       026D  _angle_upper_byte_4C
       026F  _angle_lower_byte_4B
       0271  _angle_upper_byte_4B
       0273  _angle_lower_byte_4A
       0274  _angle_upper_byte_4A
       0275  _angle_lower_byte_3C
       0277  _angle_upper_byte_3C
       0279  _angle_lower_byte_3B
       027B  _angle_upper_byte_3B
       027D  _angle_lower_byte_3A
       027E  _angle_upper_byte_3A
       027F  _angle_lower_byte_2C
       0281  _angle_upper_byte_2C
       0283  _angle_lower_byte_2B
       0285  _angle_upper_byte_2B
       0287  _angle_lower_byte_2A
       0288  _angle_upper_byte_2A
       0289  _angle_lower_byte_1C
       028B  _angle_upper_byte_1C
       028D  _angle_lower_byte_1B
       028F  _angle_upper_byte_1B
       0291  _angle_lower_byte_1A
       0292  _angle_upper_byte_1A
       0293  _time_temp
       0294  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0068 =    104. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\Softwares\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
dance_moves.o	[ dance_moves.c ]
<library>	[ div16u.s, emul16s.s, gpop3.s, gpush.s, gpushx.s, gpushy.s, gpushz.s, gpusha.s, gpushb.s ]

User Global Definitions

ram_end = 0x21ff
hwstk_size = 0x1e

Area Definitions

-bfunc_lit:0xe4.0x10000
-bdata:0x200.0x21ff

