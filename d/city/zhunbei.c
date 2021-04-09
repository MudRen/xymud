inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",HIC"新手准备室"NOR);
        set("long", "这里是新手准备室，小雨在这儿负责给新手发装备。\n");
        set("long2","以下是新手可以要到的装备，你可以用yao 来要装备(比如yao sword)：
──────────────────────────────
盔甲：
          甲(armor)        靴(shoes)     盾(shield)
          盔(kui)          衣(cloth)     披风(pifeng)
兵器：
          棒(stick)        剑(sword)     筋(whip)
          刀(blade)        爪(zhua)      杖(staff)
          斧(axe)          铲(fork)      锤(hammer)
          枪(spear)        琴(qin)       锏(mace)
          匕首(dagger)
特殊:
          天师法冠(bonnet)    松鹤龟苓膏(gao)
──────────────────────────────\n"HIY"\n\t每人每天可以向小雨要三次松鹤龟苓膏("HIR"gao"HIY")哦\n\n\n"NOR
        );
        set("exits", ([
                "south" : __DIR__"kezhan",
        ]));
        set("objects", 
        ([ 
                        __DIR__"npc/vikee" : 1,
        ]));
        set("no_fight", 1);
        set("no_magic", 1);
        setup();
}
