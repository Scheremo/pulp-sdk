// #define STIM_W_SIZE 288
// // weights [1 x 8 x 3 x 3 x 4]
// uint8_t __attribute__((section(".heapsram"))) neureka_weights[] = {
//   0x74,
//   0xb2,
//   0x61,
//   0x05,
//   0x8b,
//   0x84,
//   0xa9,
//   0x04,
//   0xce,
//   0x1b,
//   0xaa,
//   0x02,
//   0x96,
//   0x08,
//   0xed,
//   0x01,
//   0xc4,
//   0xa5,
//   0x8c,
//   0x00,
//   0x2c,
//   0xab,
//   0x27,
//   0x03,
//   0x55,
//   0x66,
//   0x69,
//   0x0a,
//   0x93,
//   0x43,
//   0xfa,
//   0x0b,
//   0xf4,
//   0x62,
//   0xf6,
//   0x0c,
//   0x5c,
//   0xbf,
//   0xaa,
//   0x07,
//   0xb5,
//   0x50,
//   0x95,
//   0x07,
//   0xc9,
//   0xa4,
//   0xd7,
//   0x03,
//   0x4b,
//   0xca,
//   0x1b,
//   0x07,
//   0x2c,
//   0xa8,
//   0x4f,
//   0x09,
//   0xdc,
//   0xcb,
//   0x5c,
//   0x09,
//   0xf8,
//   0x2a,
//   0xaf,
//   0x07,
//   0x01,
//   0xad,
//   0xe0,
//   0x0f,
//   0xd4,
//   0x1d,
//   0xb4,
//   0x01,
//   0xe5,
//   0x36,
//   0x9f,
//   0x09,
//   0x7b,
//   0xb4,
//   0x3c,
//   0x02,
//   0x85,
//   0x12,
//   0x00,
//   0x0e,
//   0x15,
//   0x54,
//   0x0b,
//   0x0e,
//   0x58,
//   0xd1,
//   0x62,
//   0x0d,
//   0xb1,
//   0x51,
//   0xae,
//   0x00,
//   0x37,
//   0x91,
//   0x0f,
//   0x0c,
//   0x99,
//   0xcb,
//   0xcf,
//   0x02,
//   0x92,
//   0x60,
//   0xb0,
//   0x09,
//   0x19,
//   0x83,
//   0xf6,
//   0x03,
//   0xf5,
//   0x8a,
//   0xd2,
//   0x04,
//   0x33,
//   0x7d,
//   0x8e,
//   0x0e,
//   0x11,
//   0x14,
//   0x16,
//   0x05,
//   0x35,
//   0x95,
//   0x0f,
//   0x0a,
//   0x7e,
//   0x2d,
//   0xb9,
//   0x03,
//   0x4e,
//   0xc6,
//   0xb3,
//   0x06,
//   0xb7,
//   0x1c,
//   0x89,
//   0x0c,
//   0x7d,
//   0x9e,
//   0xd4,
//   0x08,
//   0xab,
//   0x41,
//   0xea,
//   0x06,
//   0xd8,
//   0x91,
//   0x52,
//   0x09,
//   0x0f,
//   0xfa,
//   0x02,
//   0x0c,
//   0xdd,
//   0x4f,
//   0x29,
//   0x01,
//   0x23,
//   0x2d,
//   0x99,
//   0x0a,
//   0xa8,
//   0xad,
//   0xff,
//   0x03,
//   0xa2,
//   0x36,
//   0x0d,
//   0x08,
//   0x86,
//   0xda,
//   0xc3,
//   0x0c,
//   0xc7,
//   0x08,
//   0xed,
//   0x05,
//   0x05,
//   0x1c,
//   0x6d,
//   0x04,
//   0x36,
//   0x67,
//   0x79,
//   0x06,
//   0x9e,
//   0x30,
//   0x9a,
//   0x05,
//   0x99,
//   0x46,
//   0x26,
//   0x0a,
//   0xe8,
//   0xd3,
//   0x7b,
//   0x07,
//   0x62,
//   0xd5,
//   0xa7,
//   0x08,
//   0x90,
//   0x5c,
//   0xe6,
//   0x0c,
//   0xfb,
//   0x7c,
//   0x74,
//   0x06,
//   0x76,
//   0x90,
//   0xe2,
//   0x04,
//   0x5d,
//   0x5c,
//   0xac,
//   0x02,
//   0x53,
//   0xe6,
//   0x58,
//   0x0c,
//   0x02,
//   0x78,
//   0xb1,
//   0x09,
//   0xdd,
//   0x43,
//   0x9f,
//   0x07,
//   0x18,
//   0x93,
//   0x7b,
//   0x04,
//   0xce,
//   0x3d,
//   0xe5,
//   0x09,
//   0xa4,
//   0xc4,
//   0x6f,
//   0x0c,
//   0xdd,
//   0xbc,
//   0x2e,
//   0x06,
//   0x06,
//   0x4c,
//   0xe2,
//   0x06,
//   0xa2,
//   0xa3,
//   0x13,
//   0x0d,
//   0xac,
//   0x19,
//   0xa7,
//   0x03,
//   0xec,
//   0x87,
//   0x4f,
//   0x06,
//   0x22,
//   0xbc,
//   0xe0,
//   0x08,
//   0xc7,
//   0x6c,
//   0x84,
//   0x03,
//   0x11,
//   0xc2,
//   0x5a,
//   0x06,
//   0x5b,
//   0x3b,
//   0x90,
//   0x03,
//   0x22,
//   0x43,
//   0xd1,
//   0x09,
//   0xf9,
//   0xf3,
//   0x1d,
//   0x0b
// };

