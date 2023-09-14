#ifndef BITFILDS_H
#define BITFILDS_H
#include <stdint.h>
typedef struct {
   uint16_t     ready_rev   :1,
                forvard     :1,
                reset       :1,
                sel_f1      :1,
                sel_f2      :1,
                sel_f3      :1,
                remote      :1,
                rem_forvard :1,
                air_sens    :1,
                avost       :1,
                qf1_on      :1,
                qf2_on      :1,
                qf3_on      :1,
                qf4_on      :1,
                rem_rev     :1,
                di15        :1;
} tdi;

typedef struct {
   uint16_t     err_ind     :1,
                ready_on_ind:1,
                qf_off_inv  :1,
                vuf_on      :1,
                err_asu_inv :1,
                on_asu      :1,
                do6         :1,
                do7         :1,
                do8         :1,
                do9         :1,
                do10        :1,
                do11        :1,
                do12        :1,
                do13        :1,
                do14        :1,
                do15        :1;
} tdo;

typedef struct {
   uint16_t     wo_power    :1,
                w_inp_power :1,
                r2          :1,
                r3          :1,
                r4          :1,
                r5          :1,
                r6          :1,
                r7          :1,
                r8          :1,
                r9          :1,
                r10         :1,
                r11         :1,
                r12         :1,
                r13         :1,
                r14         :1,
                r15         :1;
} tentests;

typedef struct {
  uint32_t      gate0       :1,
                gate1       :1,
                gate2       :1,
                gate3       :1,
                gate4       :1,
                gate5       :1,
                gate6       :1,
                gate7       :1,
                gate8       :1,
                gate9       :1,
                gate10      :1,
                gate11      :1,
                gate12      :1,
                gate13      :1,
                gate14      :1,
                gate15      :1,
                gate16      :1,
                gate17      :1,
                gate18      :1,
                gate19      :1,
                gate20      :1,
                gate21      :1,
                gate22      :1,
                gate23      :1,
                gate24      :1,
                gate25      :1,
                gate26      :1,
                gate27      :1,
                gate28      :1,
                gate29      :1,
                gate30      :1,
                gate31      :1;
  uint16_t      gate32      :1,
                gate33      :1,
                gate34      :1,
                gate35      :1,
                r           :6,
                test_fsm    :1,
                test_rect   :1,
                test_output :1,
                test_1ms    :1,
                test_auto   :1,
                test        :1;
} tgates;

typedef struct {
  uint8_t      data;
  uint8_t      cs;

} tflash;

typedef struct {
   uint16_t     da_plus     :1,
                da_minus    :1,
                db_plus     :1,
                db_minus    :1,
                dc_plus     :1,
                dc_minus    :1,
                r6          :1,
                r7          :1,
                r8          :1,
                r9          :1,
                r10         :1,
                r11         :1,
                r12         :1,
                r13         :1,
                r14         :1,
                r15         :1;
} tdnt;

typedef struct {
   uint16_t     start       :1,
                stop        :1,
                reset_err   :1,
                reverse     :1,
                ready       :1,
                off         :1,
                r6          :1,
                r7          :1,
                r8          :1,
                r9          :1,
                r10         :1,
                r11         :1,
                r12         :1,
                r13         :1,
                r14         :1,
                r15         :1;
} tcommandbits;

typedef struct {
   uint16_t     wrk         :1,//1  Работа в автоматическом режиме
                reverse     :1,//2  Реверс + к работе
                stest_rect  :1,//4  Режим тестирования выпрямителей
                stest_fsm   :1,//8  Режим тестирования FSM
                err         :1,//16 Общая ошибка
                s_i_lim     :1,//32 Ограничение тока
                r6          :1,
                r7          :1,
                r8          :1,
                r9          :1,
                r10         :1,
                r11         :1,
                r12         :1,
                r13         :1,
                r14         :1,
                r15         :1;
} tstatusbits;

typedef struct {
   uint16_t     ready       :1,//1  Готовность
                remote      :1,//2  Дистанционное управление
                pot         :1,//4  Управление заданиями от потенциометров
                pan         :1,//8  Управление заданиями с панели оператора
                rem         :1,//16 Управление заданиями удаленно от аналоговых входов
                on          :1,//32 Автоматы включены
                w4on        :1,//64 ожидание включения автоматов
                w4on_pulsed :1,//128 Моргающий 1Гц - для индикации необходимости ручного включения автоматов
                wrk_wo_err  :1,//256 Сигнал работы без учета остановки по ошибке
                uf          :1,//512 Управление U/F
                r10         :1,
                r11         :1,
                r12         :1,
                r13         :1,
                r14         :1,
                r15         :1;
} tstatusbits2;

typedef struct {
   uint16_t     err         :1,//1  Общая ошибка
                avost       :1,//2  Нажат авар стоп
                ixad_max    :1,//4  КЗ моста АX
                iybd_max    :1,//8  КЗ моста BY
                icd_max     :1,//16 КЗ моста C
                iod_max     :1,//32 КЗ выхода
                usw_gate_min:1,//64 КЗ ключа ВУФ
                vpcb        :1,//128 Питания платы
                err_dnt     :1,//256 Ошибка ДНТ - в течение периода не было разрешения работы фазы
                uvs         :1,//512 Нет напряжения на тиристоре при запуске
                eeprom      :1,//1024 не удалось получить данные от EEPROM
                qf          :1,//2048 произошло отключение автоматического выключателя во время работы
                ovl         :1,//4096 перегрузка по входу
                vinp_min    :1,//8192 выход питаний за пределы
                vinp_max    :1,//16384
                cool        :1;//32768 возд. охлаждение
} terrbits;

typedef struct {
   uint16_t     usab_max    :1,//1
                usab_min    :1,//2
                usbc_max    :1,//4
                usbc_min    :1,//8
                usca_max    :1,//16
                usca_min    :1,//32
                uxaab_max    :1,//64
                uxaab_min    :1,//128
                uxabc_max    :1,//256
                uxabc_min    :1,//512
                uxaca_max    :1,//1024
                uxaca_min    :1,//2048
                uybab_max    :1,//4096
                uybab_min    :1,//8192
                uybbc_max    :1,//16384
                uybbc_min    :1;//32768
    uint16_t    uybca_max    :1,//1
                uybca_min    :1,//2
                ucab_max    :1,//4
                ucab_min    :1,//8
                ucbc_max    :1,//16
                ucbc_min    :1,//32
                ucca_max    :1,//64
                ucca_min    :1,//128
                r8          :1,//256
                r9          :1,//512
                r10         :1,//1024
                r11         :1,//2048
                r12         :1,//4096
                r13         :1,//8192
                r14         :1,//16384
                r15         :1;//32768
} terrbits_volt;

typedef struct {
   uint16_t     u24V_max    :1,//1
                u24V_min    :1,//2
                u12V_max    :1,//4
                u12V_min    :1,//8
                u5V_max     :1,//16
                u5V_min     :1,//32
                u350V_max   :1,//64
                u350V_min   :1,//128
                u3V3_max    :1,//256
                u3V3_min    :1,//512
                ugate_max   :1,//1024
                ugate_min   :1,//2048
                r12         :1,//4096
                r13         :1,//8192
                r14         :1,//16384
                r15         :1;//32768
} terrbits_pcb;

typedef struct {
   uint16_t     qf1         :1,//1
                qf2         :1,//2
                qf3         :1,//4
                qf4         :1,//8
                r4          :1,//16
                r5          :1,//32
                r6          :1,//64
                r7          :1,//128
                r8          :1,//256
                r9          :1,//512
                r10         :1,//1024
                r11         :1,//2048
                r12         :1,//4096
                r13         :1,//8192
                r14         :1,//16384
                r15         :1;//32768
} terrbits_qf;

typedef struct {
   uint16_t     ixaa        :1,//1
                ixab        :1,//2
                ixac        :1,//4
                iyba        :1,//8
                iybb        :1,//16
                iybc        :1,//32
                ica         :1,//64
                icb         :1,//128
                icc         :1,//256
                r9          :1,//512
                r10         :1,//1024
                r11         :1,//2048
                r12         :1,//4096
                r13         :1,//8192
                r14         :1,//16384
                r15         :1;//32768
} terrbits_ovl;


typedef struct {//Комманды
                uint16_t    read                    :1,//1030 1      Общее чтение (как при Init)
                            write                   :1,//2      Общая запись
                            read_compl              :1,//4      Чтение только настроек комплекта
                            write_compl             :1,//8      Запись только настроек комплета
                            read_common_factory     :1,//16
                            write_common_factory    :1,//32
                            read_complect_factory   :1,//64
                            write_complect_factory  :1,//128
                            read_common_factorye    :1,//256
                            write_common_factorye   :1,//512
                            read_complect_factorye  :1,//1024
                            write_complect_factorye :1,//2048
                            refresh_common          :1,//4096
                            refresh_complect        :1,//8192
                            error                   :1,//16384
                            apply2FPGA              :1;//32768
} tscommand; //В составе ttests

typedef struct {//Биты различой конфигурации оборудования
                uint16_t    sync_lin                :1,//1626  1- синхронизация выпрямителей от линейного напряжения 0-от фазного
                            en_alfa0                :1,//2 1-Разрешить "сеточное включение" те прохождение максимального угла включенной фазы при наличии тока ы других двух
                            r2                      :1,//4
                            r3                      :1,//8
                            r4                      :1,//16
                            r5                      :1,//32
                            r6                      :1,//64
                            r7                      :1,//128
                            r8                      :1,//256
                            r9                      :1,//512
                            r10                     :1,//1024
                            r11                     :1,//2048
                            r12                     :1,//4096
                            r13                     :1,//8192
                            r14                     :1,//16384
                            r15                     :1;//32768
} tsconfigbits;

typedef struct {//Биты статуса доп прерываний от FPGA
                uint8_t     uart2_irq_req_rx        :1,//1
                            uart2_irq_req_tx        :1,//2
                            r2                      :1,//4
                            r3                      :1,//8
                            r4                      :1,//16
                            r5                      :1,//32
                            r6                      :1,//64
                            r7                      :1;//128
} tintstatus;




typedef struct {//Диагностики 0xffffffff- все включены
                uint16_t    global :1,
                            avost  :1,
                            r             :14;
                uint16_t    r2;
} tdiags; //

#endif // BITFILDS_H
