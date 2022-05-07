/*Лабораторная работа №9
«BMP»

Выполните рефакторинг кода, который был приведен на лекции. Что понимается под рефакторингом:

1.Создание класса BMP.
2.Определение методов чтения и записи изображения.
3.Разбиение кода на дополнительные функции по вашему усмотрению.
4.Переименование переменных по вашему усмотрению.
5.Добавить 1 фильтр для изображения.*/
#include <iostream>
#include <fstream>

#pragma pack(1) // Отключить выравнивание
struct BMPHEADER
{
    unsigned short    Type;
    unsigned int      Size;
    unsigned short    Reserved1;
    unsigned short    Reserved2;
    unsigned int      OffBits;
};
#pragma pack()

#pragma pack(1)
struct BMPINFO
{
    unsigned int    Size;
    int             Width;
    int             Height;
    unsigned short  Planes;
    unsigned short  BitCount;
    unsigned int    Compression;
    unsigned int    SizeImage;
    int             XPelsPerMeter;
    int             YPelsPerMeter;
    unsigned int    ClrUsed;
    unsigned int    ClrImportant;
};
#pragma pack()

#pragma pack(1)
struct Pixel
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
};
#pragma pack()
class BMP
{
public:
    BMP()
    {
        m_width = 0;
        m_height = 0;
    }
    BMP(std::string s)
    {
        // Чтение файла
        std::ifstream in(s, std::ios::binary); // открыть файл для бинарного чтения


        // Считать 14 байтов побайтово и заполнить структуру BMPHEADER
        in.read(reinterpret_cast<char*>(&m_bmpHeader), sizeof(BMPHEADER));


        in.read(reinterpret_cast<char*>(&m_bmpInfo), sizeof(BMPINFO));

        m_width = m_bmpInfo.Width;
        m_height = m_bmpInfo.Height;

        m_pixels = new Pixel * [m_bmpInfo.Height];
        for (int i = 0; i < m_bmpInfo.Height; i++)
            m_pixels[i] = new Pixel[m_bmpInfo.Width];

        for (int i = 0; i < m_bmpInfo.Height; i++)
        {
            for (int j = 0; j < m_bmpInfo.Width; j++)
                in.read(reinterpret_cast<char*>(&m_pixels[i][j]), sizeof(Pixel));

            if ((3 * m_bmpInfo.Width) % 4 != 0)
                for (int j = 0; j < 4 - (3 * m_bmpInfo.Width) % 4; j++)
                {
                    char c;
                    in.read(&c, 1);
                }
        }
    }
    ~BMP()
    {

    }
    void ReadFile(std::string s)
    {
        // Чтение файла
        std::ifstream in(s, std::ios::binary); // открыть файл для бинарного чтения
        // Считать 14 байтов побайтово и заполнить структуру BMPHEADER
        in.read(reinterpret_cast<char*>(&m_bmpHeader), sizeof(BMPHEADER));
        in.read(reinterpret_cast<char*>(&m_bmpInfo), sizeof(BMPINFO));

        m_width = m_bmpInfo.Width;
        m_height = m_bmpInfo.Height;

        m_pixels = new Pixel * [m_bmpInfo.Height];
        for (int i = 0; i < m_bmpInfo.Height; i++)
            m_pixels[i] = new Pixel[m_bmpInfo.Width];

        for (int i = 0; i < m_bmpInfo.Height; i++)
        {
            for (int j = 0; j < m_bmpInfo.Width; j++)
                in.read(reinterpret_cast<char*>(&m_pixels[i][j]), sizeof(Pixel));

            if ((3 * m_bmpInfo.Width) % 4 != 0)
                for (int j = 0; j < 4 - (3 * m_bmpInfo.Width) % 4; j++)
                {
                    char c;
                    in.read(&c, 1);
                }
        }
    }

    void Save(std::string s)
    {
        if (m_height == 0 || m_width == 0)
        {
            throw std::exception("Пустой файл");
        }
        std::ofstream out(s, std::ios::binary);

        int width = m_bmpInfo.Width;
        int height = m_bmpInfo.Height;
        // Формирование заголовка
        BMPHEADER bmpHeader_new;
        bmpHeader_new.Type = 0x4D42; // Тип данных BMP
        bmpHeader_new.Size = 14 + 40 + (3 * width * height);
        if (width % 4 != 0)
            bmpHeader_new.Size += (4 - (3 * width) % 4) * height;
        bmpHeader_new.OffBits = 54;
        bmpHeader_new.Reserved1 = 0;
        bmpHeader_new.Reserved2 = 0;

        out.write(reinterpret_cast<char*>(&bmpHeader_new), sizeof(BMPHEADER));

        // Формирование информации об изображении
        BMPINFO bmpInfo_new;
        bmpInfo_new.BitCount = 24;
        bmpInfo_new.ClrImportant = 0;
        bmpInfo_new.ClrUsed = 0;
        bmpInfo_new.Compression = 0;
        bmpInfo_new.Height = height;
        bmpInfo_new.Planes = 1;
        bmpInfo_new.Size = 40;
        bmpInfo_new.SizeImage = bmpHeader_new.Size - 54;
        bmpInfo_new.Width = width;
        bmpInfo_new.XPelsPerMeter = 0;
        bmpInfo_new.YPelsPerMeter = 0;

        out.write(reinterpret_cast<char*>(&bmpInfo_new), sizeof(BMPINFO));

        // Записать пиксели
        for (int i = 0; i < bmpInfo_new.Height; i++)
        {
            for (int j = 0; j < bmpInfo_new.Width; j++)
                out.write(reinterpret_cast<char*>(&m_pixels[i][j]), sizeof(Pixel));

            if ((3 * bmpInfo_new.Width) % 4 != 0)
                for (int j = 0; j < 4 - (3 * bmpInfo_new.Width) % 4; j++)
                {
                    char c = 0;
                    out.write(&c, 1);
                }
        }

    }
    void MirorColor()
    {
        for (int i = 0; i < m_bmpInfo.Height; i++)
            for (int j = 0; j < m_bmpInfo.Width; j++)
            {
                int big = 2, mid = 1, low = 0;
                if (m_pixels[i][j].b <= m_pixels[i][j].g && m_pixels[i][j].b <= m_pixels[i][j].r)
                {
                    if (m_pixels[i][j].r >= m_pixels[i][j].g)
                    {
                        std::swap(m_pixels[i][j].r, m_pixels[i][j].b);
                    }
                    else
                    {
                        std::swap(m_pixels[i][j].g, m_pixels[i][j].b);
                    }
                }
                else if (m_pixels[i][j].b <= m_pixels[i][j].g || m_pixels[i][j].b <= m_pixels[i][j].r)
                {
                    std::swap(m_pixels[i][j].g, m_pixels[i][j].r);
                }
                else
                {
                    if (m_pixels[i][j].r >= m_pixels[i][j].g)
                    {
                        std::swap(m_pixels[i][j].g, m_pixels[i][j].b);
                    }
                    else
                    {
                        std::swap(m_pixels[i][j].r, m_pixels[i][j].b);
                    }
                }
            }


    }
    void Negative()
    {
        for (int i = 0; i < m_bmpInfo.Height; i++)
            for (int j = 0; j < m_bmpInfo.Width; j++)
            {
                m_pixels[i][j].b = 255 - m_pixels[i][j].b;
                m_pixels[i][j].g = 255 - m_pixels[i][j].g;
                m_pixels[i][j].r = 255 - m_pixels[i][j].r;
            }
    }
    void Encrypt()
    {
        for (int i = 0; i < m_bmpInfo.Height; i++)
            for (int j = 0; j < m_bmpInfo.Width; j++)
            {
                if (m_pixels[i][j].b != m_pixels[1][1].b || m_pixels[1][1].g != m_pixels[1][1].g || m_pixels[1][1].r != m_pixels[1][1].r)
                {
                    m_pixels[i][j].b = m_pixels[0][0].b;
                    m_pixels[i][j].g = m_pixels[0][0].g;
                    m_pixels[i][j].r = m_pixels[0][0].r-1;
                }
            }
        int co = m_pixels[0][0].b;
        std::cout << co;
    }
    void Decipher()
    {
        
        int co = m_pixels[0][0].b;
        std::cout << co;
        for (int i = 0; i < m_bmpInfo.Height; i++)
            for (int j = 0; j < m_bmpInfo.Width; j++)
            {
                if (m_pixels[i][j].r != co)
                {
                    m_pixels[i][j].b = 100;
                    m_pixels[i][j].g = 200;
                    m_pixels[i][j].r = 100;
                }
            }
    }
private:
    BMPHEADER m_bmpHeader;
    BMPINFO m_bmpInfo;
    Pixel** m_pixels;
    int m_width, m_height;
};

int main()
{
    std::string in = "im.bmp";
    std::string s1 = "encrypted.bmp";
    std::string s2 = "decrypted.bmp";
    

    try
    {
        BMP newbmp(in);
        newbmp.Encrypt();
        newbmp.Save(s1);
        BMP newbmp2(s1);
        newbmp2.Decipher();
        newbmp2.Save(s2);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }



}

