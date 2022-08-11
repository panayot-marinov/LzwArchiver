#pragma once
#ifndef ARCHIVE_HEADER_HPP
#define ARCHIVE_HEADER_HPP

#include <cstdint>

struct ArchiveHeader
{
    static constexpr char TYPE_REGULAR_FILE[2] = "1";
    static constexpr char TYPE_DIRECTORY[2] = "2";

    uint64_t chksum;
    char name[100];
    unsigned int size;
    //char mtime[12];
    char type[2];
    

    void calculateChecksum()
    {
        // this->chksum =
        //     (sizeof(chksum) / sizeof(char)) + sizeof(' ') +
        //     (sizeof(name) / sizeof(char)) + sizeof(' ') +
        //     (sizeof(size) / sizeof(char)) + sizeof(' ') +
        //     (sizeof(mtime) / sizeof(char)) + sizeof(' ') +
        //     (sizeof(type) / sizeof(char));

        this->chksum = 5;
    }

    // private:
    //     unsigned int checksumOfCharArray(char arr[])
    //     {
    //         for (size_t i = 0; i < sizeof(arr) / sizeof(char); i++)
    //         {
    //             for (size_t j = 0; j < 8; j++)
    //             {

    //             }
    //         }
    //     }

    //     unsigned int checksumOfUnsignedInt(int num)
    //     {
    //     }
};

#endif