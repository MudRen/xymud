// gate.c

#include <ansi.h>

inherit ROOM;

void create ()
{
  set ("short", "[1;37mé´é³ç[2;37;0m");
  set ("long", @LONG

éçº¦åæ¹ç°åºä¸åº§é»è²åæ¥¼ï¼åçº¿å¤ªæï¼çä¸å¤§æ¸æ¥ãè®¸å¤äº¡é­æ­£
å­å­å¼å¼å°åéåè¿ï¼å ä¸ºä¸è¿é¬¼é¨å³å°±æ æ³ååé³é´äºãå¨å´å°º
é«çéèéé£ææï¼èä¸­ååºå¼å¼çé£å£°ã
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"new-out2",
  "north" : __DIR__"new-out6",
  "west": __DIR__"new-out8",
  "east": __DIR__"new-out4",
]));
	set("no_fight", 1);
	set("no_magic",1);
  set("hell", 1);
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/pang" : 1,
     //éé¦æé¬¼ä»»å¡
//      "/quest/æé¬¼/npc/kui" : 1,
]));

  setup();
}
