#ifndef CARD_H
#define CARD_H

#include <string>

struct Card
{
   std::string Name;
   std::string FileName;
   std::string URL;
   std::string ThumbURL;
   int x;
   int y;
   int w;
   int h;

   void dump(void);
};

#endif
