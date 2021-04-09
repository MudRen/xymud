//mugu.c
#include <ansi.h>
inherit NPC;

string ask_for_leave();
string check_me();

void create()
{
        set_name("麻姑", ({"magu"}));
        set("gender", "女性" );
        set("age", 30);
        set("title","月宫管家");
        set("long", "麻姑在月宫可是里里外外一把手。\n");
	set_level(40);
        set("attitude", "peaceful");
        set("inquiry", ([
		"脱离" : (: ask_for_leave :),
		"leave" : (: ask_for_leave :),
		"拜师" : (: check_me :),
	]) );
	set_skill("literate", 320);
	set_skill("unarmed", 350);
       	set_skill("dodge", 380);
       	set_skill("force", 350);
       	set_skill("parry", 350);
       	set_skill("sword", 350);
       	set_skill("spells", 350);
        set_skill("moonshentong",360);
        set_skill("baihua-zhang", 360);
        set_skill("moonforce", 360);
        set_skill("snowsword", 360);
        set_skill("moondance", 360);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("dodge", "moondance");
	create_family("月宫", 3, "弟子");	
	setup();
	carry_object("/d/obj/book/san.c");
	carry_object("/d/obj/book/girlbook");
        carry_object("/d/ourhome/obj/pink_cloth")->wear();
        carry_object("/d/ourhome/obj/shoes")->wear();
}

void init()
{
        add_action("do_agree", "agree");
}

string ask_for_leave()
{
	object me=this_player();
       	if( me->query_level()<40 )
		return "莫非你是来卧底的？";
	if (me->query("family/family_name") == "月宫" ) 
	{
		command("say 你既是执意下山，老身却有几句话说。");
		me->set_temp("betray", 1);
		return ("叛出师门要需要有一定惩罚，你可愿意(agree)？");
	}
	return ("老身不知。\n");
}

int do_agree(string arg)
{
	if( this_player()->query_temp("betray") 
	 && this_player()->query("family/family_name")=="月宫") 
	 {
		if( FAMILY_D->leave_family(this_player(),this_object()) )
		{
			message_vision("$N答道：弟子愿意。\n\n", this_player());
			command("say 既是你与月宫无缘，你便下山去吧！");
			return 1;
		}	
	}
	return 0;
}

void story_end()
{
	string name,*names;
	object pre_ob,me,seed;
	
	pre_ob = previous_object(0);
	me = pre_ob->query("give_letter");
	pre_ob->delete("give_letter");
	if( !me || !living(me) )
		return;
	me->set_temp("pedding/moon_wangfangping",1);
	seed = new("/d/obj/misc/seed");
	seed->set("owner_id",me->query("id"));
	if( !seed->move(me) )
		seed->move(environment(me));
	message_vision("王方平从怀中掏出一件物什交给$N。\n",me);
	names = ({
		HIB "蓝玫瑰" NOR,
		HIB "黑郁金香" NOR,
    		HIB "薄雪花" NOR,
    		HIB "野风信子" NOR,
    		HIB "玉白露" NOR,
    		HIB "睡芙蓉" NOR,
    		HIB "紫蔷薇" NOR,
    		HIB "大丽花" NOR,
    		HIB "勿忘我" NOR,
    		HIB "白玫瑰" NOR,
    		HIB "翡翠绿" NOR,
    		HIB "雪腊梅" NOR,
    		HIB "曼陀罗" NOR,
    		HIB "睡莲" NOR,		
	});
	name = me->query("family/moon_magu");
	if( !name || !stringp(name) )
		name = names[random(sizeof(names))];
	tell_object(me,HIG"王方平在你耳边说道：我给你一粒"+name+HIG"的种子，你待其成熟后交予麻姑，她自知结果。\n"NOR);
	me->set("family/moon_magu",name);
	return;
}	

string check_me()
{
	string *story;
	object obj,me = this_player();
	if( !userp(me) || me->query("family/family_name")=="月宫" )
		return 0;
	if( me->query_temp("mark/moon_class") )
		return "呵呵，你太客气了。";
	if( me->query("class")=="xian" )
		return "呵呵，这怎么敢当。";
	if( me->query_temp("pedding/moon_magu") )
		return "还不速速去办？";
	if( me->query_temp("pedding/moon_wangfangping") )
		return "王方平怎么说？";
	if( query("give_letter") )
		return "此事已托"+query("give_letter")->name()+"去办了。";
	me->set_temp("pedding/moon_magu",1);
	obj = new("/d/moon/obj/paper");
	obj->set("owner_id",me->query("id"));
	obj->set("target_id","wang fangping");
	story = ({
		"$N呵呵一笑：自汉孝恒帝以来，某与上真真君已有多载未见。\n",
		CYN"$N说道：沧海桑田，吾等修真之人，白马过隙。\n"NOR,
		"$N对$n呵呵一笑：偶有感伤，倒叫汝见笑了。\n",
		CYN"$N说道：看看仙姑来函倒是说了些什么。\n",
		"$N拆开了信函。\n",
		"$N仔细看了看信函。\n",
		"$N眉头皱了皱，低头沉思片刻。\n",
		CYN"$N说道：此事还得从长计议，你待我与同门商量一番。\n"NOR,
		"$N念叨几句咒语，化出一只鬼鸦，径往地府各殿而去。\n",
		"......\n",
		"\n",
		"\n",
		"只见数只鬼鸦从各司飞来，在$N耳边喃喃说了数语。\n",
		"$N面带喜色。\n",
	});		
	obj->set("story",story);
	obj->set("fuction", (: call_other, __FILE__, "story_end" :));	
	obj->set("long",sprintf(obj->query("long"),"麻姑","王方平"));
	if( obj->move(me) )
	{
		set("give_letter",me);
		return "我与那王方平有旧，此处有一书函，你替我交予他，看看他有何回应。";	
	}
	else
	{
		if( obj ) destruct(obj);
		return "你身上杂物太多，我可不放心交给你。";
	}	
}

int accept_object(object who,object obj)
{
	if( !who->query("family/moon_magu") )
		return 0;
	if( base_name(obj)!="/d/obj/misc/flower" )
		return 0;
	if( obj->query("name")!=who->query("family/moon_magu") )
		return 0;
	EMOTE_D->do_emote(this_object(), "ah",geteuid(who),CYN,0,0,0);
	tell_object(who,HIY"麻姑看着你手中的"+obj->name()+HIY"，低头思索了片刻。\n"NOR);
	EMOTE_D->do_emote(this_object(), "oh",geteuid(this_object()),CYN,0,0,0);
	EMOTE_D->do_emote(this_object(), "thank",geteuid(who),CYN,0,0,0);
	command("chat* gongxi");
	who->set_temp("mark/moon_class",1);
	tell_object(who,HIY"【师门】你完成了月宫的门派试炼任务，你可以带艺加入月宫了。\n"NOR);
	tell_object(who,HIR"注意：门派试炼任务记录下线会自动清除。\n"NOR);
	tell_object(who,CYN"麻姑说道：事不宜迟，"+RANK_D->query_respect(who)+"还是赶紧去找合适的师傅吧。\n"NOR);
	return 1;	
}