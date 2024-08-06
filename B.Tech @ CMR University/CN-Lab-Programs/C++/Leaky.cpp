// Copyright (C) 2021 Kritik Agarwal <https://github.com/Kritik007>
 
// Write a program for congestion control using Leaky bucket algorithm.


#include<bits/stdc++.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define NOF_PACKETS 10

using namespace std;

int rand(int a)
{
    int rn = (rand() % 10) % a;
    return  rn == 0 ? 1 : rn;
}

int main()
{
    int packet_sz[NOF_PACKETS], i, clk, b_size, o_rate, p_sz_rm=0, p_sz, p_time, op;
    for(i = 0; i<NOF_PACKETS; ++i)
        packet_sz[i] = rand(6) * 10;
    for(i = 0; i<NOF_PACKETS; ++i)
        cout << "\npacket[" << i << "]:" << packet_sz[i] << " bytes\t";
    cout << "\nEnter the Output rate:";
    cin >> o_rate;
    cout << "Enter the Bucket Size:";
    cin >> b_size;
    for(i = 0; i<NOF_PACKETS; ++i)
    {
        if( (packet_sz[i] + p_sz_rm) > b_size)
            if(packet_sz[i] > b_size)
                cout << "\n\nIncoming packet size (" << packet_sz[i] << "bytes) is Greater than bucket capacity (" << b_size << "bytes)-PACKET REJECTED";
            else
                cout << "\n\nBucket capacity exceeded-PACKETS REJECTED!!";
        else
        {
            p_sz_rm += packet_sz[i];
            cout << "\n\nIncoming Packet size: " << packet_sz[i];
            cout << "\nBytes remaining to Transmit: " << p_sz_rm;
            p_time = rand(4) * 10;
            cout << "\nTime left for transmission: " << p_time << " units";
            for(clk = 10; clk <= p_time; clk += 10)
            {
                Sleep(1);
                if(p_sz_rm)
                {
                    if(p_sz_rm <= o_rate)
                        op = p_sz_rm, p_sz_rm = 0;
                    else
                        op = o_rate, p_sz_rm -= o_rate;
                    cout << "\nPacket of size " << op << " Transmitted";
                    cout << "----Bytes Remaining to Transmit: " << p_sz_rm;
                }
                else
                {
                    cout << "\nTime left for transmission: " << p_time-clk << " units";
                    cout << "\nNo packets to transmit!!";
                }
            }
        }
    }
}
