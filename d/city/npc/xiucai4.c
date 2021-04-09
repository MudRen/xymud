inherit SUPER_NPC;
string apply_gongming(object me);

void create()
{
        set_name("贺知章", ({"he zhizhang", "he", "zhizhang"}));
        set_level(39);
        set("gender", "男性");
        set("age", 55);
	set("title", "国子监大学士");
        set("long", "贺知章是国子监大学士，统管全国文人考试及升级。\n");
        set("attitude", "friendly");
        set("class", "scholar");
        set_skill("unarmed", 150);
        set_skill("dodge",350);
        set_skill("literate", 380);
        set_skill("parry", 350);
        set_skill("force", 350);
        set_skill("sword",400);
        set_skill("haoran-jian",400);
        map_skill("sword","haoran-jian");
        map_skill("parry","haoran-jian");
        set_skill("haoran-zhengqi",390);
        map_skill("force","haoran-zhengqi");
        
	set("inquiry", ([
		"name" : "薄名何足挂齿...老夫贺知章蒙皇上恩赏国子监大学士，实是愧不敢当。\n",
		"here" : "这里便是国子监。\n",
		"读书识字": "对了，你是来对地方了！\n",
		"学习" : "只要总管府认定，我们就收！\n",
		"功名" : (: apply_gongming :),
        ]) );
        setup();
        carry_object(0,"cloth",random(10))->wear();
}

string apply_gongming(object me)
{
        me=this_player();
        if( me->query("class") != 0 ) //means already has a class
                return "功名富贵都是过眼云烟，又何必挂在心上？\n";
	message_vision("贺知章说道：功名富贵都是过眼云烟，又何必挂在心上？\n", me);
        message_vision("贺知章对$N叹了口气道：既然你如此热衷...\n", me);
        me->set("class", "scholar");
        if( me->query_skill("literate", 1) < 200 )
        	return "以阁下的才识，还只能从童生做起。\n";
	else if( me->query_skill("literate", 1) < 400 )
        	return "以阁下的才识，做个秀才还是可以的。\n";
	else    return "以阁下的才识，做个大学士没问题。\n";
}
