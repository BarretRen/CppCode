#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    const int L1_BUFFER_HDR_SIZE = 4;
    unsigned int frame[49] = {0x2d, 0x00, 0x04, 0x00, 0x00, 0x01, 0x10, 0x1c, 0x08, 0x02, 0x01, 0x01, 0x05, 0x04, 0x03, 0x80,
                              0x90, 0xa3, 0x18, 0x03, 0xa9, 0x83, 0x81, 0x6c, 0x0d, 0x01, 0x81, 0x31, 0x33, 0x32, 0x39, 0x31,
                              0x36, 0x32, 0x30, 0x30, 0x31, 0x34, 0x70, 0x09, 0xc0, 0x38, 0x38, 0x36, 0x31, 0x38, 0x36, 0x35,
                              0x36};
    int frame_len = frame[0] + L1_BUFFER_HDR_SIZE;
    int called_start, calling_start = 0;
    char cgDigits[15] = "12345678";

    if (frame[12] == 0x5)
    {
        cout << "received SETUP message" << endl;
        //get the position of Cgpn and Cdpn
        for (int i = 13; i < frame_len; i++)
        {
            if (calling_start != 0 && called_start != 0)
            {
                break;
            }
            if (frame[i] == 0x6c)
            {
                calling_start = i;
            }
            if (frame[i] == 0x70)
            {
                called_start = i;
            }
        }

        cout << "CgPn start at " << calling_start << ", length: " << frame[calling_start + 1] << endl;

        // change TON for CgPn: 010
        frame[calling_start + 2] &= (~(1 << 6)); //bit7置0
        frame[calling_start + 2] |= (1 << 5);    //bit6置1
        frame[calling_start + 2] &= (~(1 << 4));
        cout << frame[calling_start + 2] << endl;
        //change NPI for Cgpn: 0011
        frame[calling_start + 2] &= (~(1 << 3));
        frame[calling_start + 2] &= (~(1 << 2));
        frame[calling_start + 2] |= (1 << 1);
        frame[calling_start + 2] |= (1 << 0);
        cout << frame[calling_start + 2] << endl;

        //change Cgpn digits
        // int cgDigits_len = strlen(cgDigits);
        // for (int i = 0; i < cgDigits_len; i++)
        // {
        //     frame[calling_start + 4 + i] = cgDigits[i];
        // }
        //cdpn lendth后只有两个个bit8，所以这里减2
        // for (int i = cgDigits_len; i < frame[calling_start + 1] - 2; i++)
        // {
        //     frame[calling_start + 4 + i] = 0;
        // }

        // //change CdPn digits
        // int cdDigits_len = strlen(cgDigits);
        // for (int i = 0; i < cdDigits_len; i++)
        // {
        //     frame[called_start + 3 + i] = cgDigits[i];
        // }
        // //cdpn lendth后只有一个bit8，所以这里减1
        // for (int i = cdDigits_len; i < frame[called_start + 1] - 1; i++)
        // {
        //     frame[called_start + 3 + i] = 0;
        // }


        //no cgpn digits
        // for (int i = 0; i < frame[calling_start + 1] - 2; i++)
        // {
        //     frame[calling_start + 4 + i] = 0;
        // }
        //no cgpn IE//
        //方法3： 整个IE置0,并后移
        int cgpn_len = frame[calling_start + 1] + 2;
        unsigned int tmp_frame[49];
        for (int i = 0; i < frame_len; i++)
        {
            tmp_frame[i] = frame[i];
        }
        for (int i = calling_start, j= calling_start+cgpn_len; j < frame_len; i++,j++)
        {
            frame[i] = tmp_frame[j];
        }
        for(int i = 1; i <=cgpn_len; i++)
        {
            frame[frame_len - i] = 0x00;
        }
    }

    //打印frame内容
    for (int i = 0; i < frame_len; i++)
    {
        printf("%02x  ", frame[i]);
        if ((i + 1) % 16 == 0)
            cout << endl;
    }
    return 0;
}