// by canoe
#include <ansi.h>
inherit __DIR__"try.c";

void create()
{
	set("short",HIR"剥皮地狱"NOR);
	set("long",@LONG
四周一片漆黑,耳边不时有阴风刮过.隐隐约约的鬼影到处都是.
地上散落很多刑具,这竟然就是传说中的剥皮地狱!
如果你认为肚子饿了，可以用“jinshi”让狱卒给你食物。
如果你认为你的刑期满了，可以用“out”来离开这里。

LONG
);
	set("exits",([
		"north" : __DIR__"2",
	]));
	setup();	
}