
#include "crc8.h"

byte crc(byte *ptr, int len) {
    byte crc = 0x00;

    while (len--) {
        crc = _crc_table_[crc ^ *ptr++];
    }
    return (crc);
}

byte cal_table_low_first(byte value) {
    byte i, crc;

    crc = value;
    /* 同样需要计算8次 */
    for (i = 8; i > 0; --i) {
        if (crc & 0x01) /* 反序异或变成判断最低位是否为1 */
            /* 数据变成往右移位了 */
            /* 计算的多项式从0x31（0011 0001）变成了0x8C (1000 1100) */
            /* 多项式值，原来的最高位变成了最低位，原来的最低位变成最高位，8位数据高低位交换一下位置
             */
            crc = (crc >> 1) ^ 0x8C;
        else
            crc = (crc >> 1);
    }
    return crc;
}