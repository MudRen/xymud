#include <ansi.h>
inherit ROOM;

void create()
{
  set("short", "寝室");
  set("long", @LONG

整个小庙里，也就这里还干净一些，房顶也不漏水。庙里仅剩的几个
和尚就都挤在这里。屋里处了一张长长的竹床，和挂着的几件破僧衣
之外，什么都没有。也不知这几个和尚吃什么度日。
LONG
      );
set("exits/out","/d/qujing/wudidong/bedroom-gate");
  setup();
}
