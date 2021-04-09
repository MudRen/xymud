// create by snowcat.c 12/8/1997

inherit __DIR__"midong.c";

void create_weapon()
{
	set("weapon","dao");
	set("objects",([
		__DIR__"obj/dao" : 1,
	]));	
}