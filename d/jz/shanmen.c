//Cracked by Roath
//  妖神之争 １。０
//  happ@YSZZ 2000.4.2
// /d/jz/river.c

inherit ROOM;

void create ()
{
  set ("short", "山门");
  set("long", @LONG

走到这，已经到了金山寺，寺庙不大，但是修葺的格外精致。
抬头你看见了一樽石牌。
        [1;33m
                ※※※※※※※※※※※
                ※    金  山  寺    ※
                ※※※※※※※※※※※[m
LONG);
        set("exits",([
                "westup": __DIR__"dadian",
                "eastdown": __DIR__"shanlu2",
                ]));
 setup();

}
