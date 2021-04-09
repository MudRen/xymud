inherit ROOM;
#include <ansi.h>

int block_cmd(string);
void create ()
{
  set ("short", "发呆室");
  set ("long", 
"
这是巫师为广大的发呆爱好者设计的发呆室，练习发呆神功的最好场
所，您可以在这里想尽任何办法，任何花样，各种姿势，尽情的发呆
而不会影响别人，不要再为影响市容而担心了，让我们发呆吧......
\n"
);
  set("exits", ([ /* sizeof() == 4 */
  "south" : "/d/wiz/entrance",
  "up" : "/d/city/kezhan",
]));
   set("chat_room",1);
  set("no_time",1);
  set("no_fight", 1);
  set("no_magic", 1);
       set("freeze",1);
  set("valid_startroom", 1);
  setup();
}

void init()
{
    add_action("block_cmd", "", 1);
}

int block_cmd(string args)
{
string verb;
verb = query_verb();

    if (verb == "bian") return 1; // by mon 7/15
    if (verb == "xiudao") return 1;
    if (verb == "exert") return 1;
    return 0;
}

