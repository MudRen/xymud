//【少帅府客房】
inherit ROOM;

void create()
{
        set("short", "厢房");
        set("long", @LONG
这是间整洁的厢房，因门窗常闭着，光线很昏暗。房里别无他物，
只有中间放着一张收拾得舒舒服服的大床，看着就让人想睡觉。
LONG
        );
        set("exits", ([
                "south" : __DIR__"shaoshuai2",
        ]));

        set("sleep_room", 1);
        set("no_fight", 1);
        setup();
}
