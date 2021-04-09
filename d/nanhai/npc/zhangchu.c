inherit SUPER_NPC;

string *have_yao=({});
string *have_dan=({});

string ask_yao();
string ask_dan();

void init_yao()
{
	remove_call_out("init_yao");
	if( !environment() )
		return;
        set("apply/yaono",100+random(500));
        set("apply/danno",100+random(500));
	have_yao=({});
	have_dan=({});	
	call_out("init_yao",1800);
}

void create()
{
	set_name("掌厨僧", ({ "zhangchu seng", "seng" }));
      	set_level(29);
	set("gender", "男性");
	set("age", 25);
	set("attitude", "peaceful");
	set("class", "bonze");
	set("force_factor", 10);
	set("mana_factor", 10);

	set_skill("literate", 290);
	set_skill("spells", 290);
	set_skill("buddhism", 290);
	set_skill("unarmed", 290);
	set_skill("jienan-zhi", 290);
	set_skill("dodge", 290);
	set_skill("lotusmove", 290);
	set_skill("parry", 290);
	set_skill("force", 290);
	set_skill("lotusforce", 290);
	set_skill("staff", 290);
	set_skill("lunhui-zhang", 290);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("inquiry", ([
		"云南白药": (: ask_yao :),
		"灵丹": (: ask_dan :),
	]) );
        set("apply/yaono",100+random(500));
        set("apply/danno",100+random(500));

        create_family("南海普陀山", 4, "弟子");
	
	setup();
	carry_object("/d/nanhai/obj/sengpao")->wear();
	carry_object(0,"staff",random(2))->wield();
	remove_call_out("init_yao");
	call_out("init_yao",1800);
}

string ask_yao()
{
	object ob,me = this_object(),who = this_player();
	int number;

        if( who->query("family/family_name") != "南海普陀山" ) 
		return RANK_D->query_respect(who) +"与本门毫无渊源，为什么问起这个？";
	if( objectp(ob=present("yunnan baiyao", who))
	 && base_name(ob)=="/d/nanhai/obj/yunnandrug" ) 
		return "你身上不是已经有云南白药了吗，怎么又来要？";
	if( !(number = me->query("apply/yaono"))
	 || number<=0 ) 
		return "对不起，云南白药已经全部发放出去了。";
	if(member_array(who->query("id"),have_yao)!=-1)
	    return "你不是刚刚要过吗？\n";
	
	number = 1+random(100);
	ob = new("/d/nanhai/obj/yunnandrug");
	ob->set_amount(number);
	ob->set("value",0);
	ob->set("no_put",1);
	if( ob->move(who) )
	{
		message_vision("$N递给$n"+chinese_number(number)+"颗云南白药。\n",me,who);
		have_yao+=({who->query("id")});
		set("apply/yaono",-number);
		return "云南白药得之不易，要节约着用。\n";
	}
	else
	{
		if( ob ) destruct(ob);
		return "你身上背包满了吧。";
	}
}

string ask_dan()
{
	object ob,me = this_object(),who = this_player();
	int number;

        if( who->query("family/family_name") != "南海普陀山" ) 
		return RANK_D->query_respect(who) +"与本门毫无渊源，为什么问起这个？";
	if( objectp(ob=present("ling dan", who))
	 && base_name(ob)=="/d/nanhai/obj/lingdan" ) 
		return "你身上不是已经有灵丹了吗，怎么又来要？";
	if( !(number = me->query("apply/danno"))
	 || number<=0 ) 
		return "对不起，南海灵丹已经全部发放出去了。";
	if(member_array(who->query("id"),have_dan)!=-1)
	    return "你不是刚刚要过吗？\n";

	ob = new("/d/nanhai/obj/lingdan");
	number = 1+random(100);
	ob->set_amount(number);
	ob->set("value",0);
	ob->set("no_put",1);
	if( ob->move(who) )
	{
		message_vision("$N倒出"+chinese_number(number)+"粒南海灵丹在$n手心。\n",me,who);
		have_dan+=({who->query("id")});
		set("apply/danno", -number);
		return "灵丹得之不易，要节约着用。\n";
	}
	else
	{
		if( ob ) destruct(ob);
		return "你身上背包满了吧。";
	}

}

