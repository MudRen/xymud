inherit SUPER_NPC;
void create()
{
	set_name("恶蛟", ({"dragon","jiao"}));
  	set_level(49);
  	set("gender", "男性");
  	set("long", "一条张牙舞爪的长虫，头生独角，看起来快成恶龙了。\n");
	set("attitude", "aggressive");
	set("class","dragon");
	set("age", 100);
  	set("per", 1);
  	create_family("东海龙宫", 4, "水族");
  	set("title","");
	set_skill("unarmed",490);
	set_skill("dodge",490);
	set_skill("force",490);
	set_skill("parry",490);
	set_skill("dragonfight",490);
	set_skill("dragonforce",490);
	set_skill("dragonstep",490);
	map_skill("unarmed", "dragonfight");
	map_skill("force", "dragonforce");
	map_skill("parry", "dragonfight");
	map_skill("dodge", "dragonstep");
	set_skill("zhidi-chenggang",490);
	set_skill("huanyu-hufeng",490);
	set_skill("danshan",490);
	set_skill("qiyu",490);
	set_skill("duanliu",490);
	set_skill("jiefeng",490);
	setup();
}

void die()
{
	object me,who,longjin,rope;
    	string whoid;
	string rp="/d/obj/fabao/kunxian-suo.c";
    	if( rp->in_mud() )
		rope = new(rp->query("replace_file"));
    	else	rope = new(rp);
	if( environment() ) 
		message("vision", "一阵红光闪过，恶龙落在地上。定睛一看，原来恶龙已经遁去，地上只留下一条红索。\n", environment());
	rope->move(environment(this_object()));
    	destruct(this_object());
}