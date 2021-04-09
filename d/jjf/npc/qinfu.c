inherit NPC;
#include <ansi.h>
inherit F_MASTER;

string expell_me(object me);
string check_me();

void create()
{
  set_name("秦富", ({"qin fu", "qin", "fu", "master"}));
  set_level(35);
  set("gender", "男性");
  create_family("将军府", 3, "蓝");
  set("title", "将军府管家");
  set("age", 38);
  set_skill("spear",350);
  set_skill("spells",350);
  set_skill("baguazhou",350);
  set_skill("force", 350);
  set_skill("dodge", 350);
  set_skill("parry", 350);
  set_skill("yanxing-steps", 350);
  set_skill("bawang-qiang",350);
  set_skill("lengquan-force", 350);
  set_skill("unarmed", 350);
  set_skill("changquan", 350);
  map_skill("force", "lengquan-force");
  map_skill("unarmed", "changquan");
  map_skill("spear", "bawang-qiang");
  map_skill("parry", "bawang-qiang");
  map_skill("dodge", "yanxing-steps");
  map_skill("spells","baguazhou");
  set("force_factor", 30);
  set("inquiry", ([
               "下山": (: expell_me :),
               "leave": (: expell_me :),
               "机缘" : (: check_me :),
  ]));
  setup();
  carry_object(0,"cloth",random(2))->wear();
}

void attempt_apprentice(object ob)
{
        if( ob->query("class")=="yaomo" || ob->query("class")=="ghost" )
        {
		EMOTE_D->do_emote(this_object(), "fear",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：妖怪啊！！\n"NOR);
           	return ;
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们大唐将军府发扬光大，也涨涨人族志气。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","大唐将军府又多了一个弟子  "+ob->name(1)+HIW"\n                                 将军府的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class","fighter");
}

string expell_me(object me)
{       
	me=this_player();
        if((string)me->query("family/family_name")=="将军府") {
        	if( me->query_level()<40 )
        		return "哼，翅膀还没硬就想灰了？！";
                me->set_temp("betray","jjf");
                return ("按我大唐律法，却须受罚，你可愿意(agree)?");
        }
        return 0;
}

void init()
{
	::init();
        add_action("do_agree", "agree");
}

int do_agree(string arg)
{
	if((string)this_player()->query("family/family_name")!="将军府")
		return 0;
        if(this_player()->query_temp("betray")=="jjf") 
        {
                if( FAMILY_D->leave_family(this_player(),this_object()) )
                {
                        message_vision("$N答道：弟子愿意。\n\n", this_player());
                        command("say 那你去吧！！");
                        return 1;
                }       
	}
        return 0;
}

string check_me()
{
	string *dir,name;
	object ob,me = this_player();
	if( me->query("family/family_name")=="将军府"
	 && me->query("family/master_name")=="白发老人" )
		return "加油加油！临阵磨枪，不快也光！";
	if( me->query("class")=="fighter" )
		return 0;
	if( me->query_temp("pendding/jjf_class") )
		return "不错不错。";
	if( me->query_level()<40 )
		return "现在谈这个还为时尚早。";	
	if( me->query_temp("pendding/jjf_name") )
		return "本管家还在等你的"+ me->query_temp("pendding/jjf_name") +CYN"呢。"NOR;	
	set("env/test",({"HIB","HIR","HIM","HIB","HIR","HIM",})[random(6)]);
	set_temp("weapon_level",me->query_level());
	if( random(2) )
	{
		dir = ({"armor","cloth","hand","kui","neck","pifeng","ring","shield","shoes","waist","wrists",});
		ob = new(sprintf("/d/obj/narmor/%s",dir[random(sizeof(dir))]));
		if( !ob->init_armor(this_object()) )
		{
			if( ob )  destruct(ob);
			return "我现在正忙，你稍后再来。";
		}
		name = ob->short();
	}
	else
	{
		dir = ({"axe","blade","fork","hammer","mace","spear","staff","stick","whip","sword","unarmed",});
		ob = new(sprintf("/d/obj/nweapon/%s",dir[random(sizeof(dir))]));
		if( !ob->init_weapon(this_object()) )
		{
			if( ob )  destruct(ob);
			return "我现在正忙，你稍后再来。";
		}
		name = ob->short();
	}	
	if( ob )
		destruct(ob);
	delete("env/test");
	delete_temp("weapon_level");
	delete_temp("armor_level");
	me->set_temp("pendding/jjf_name",name);
	return "前日圣上下旨，叫我等收集天下神兵利器，你去替我寻来"+name+CYN"，我自推荐你去拜老神仙为师。"NOR;
}

int accept_object(object me,object obj)
{
	if( !me->query_temp("pendding/jjf_name") )
		return 0;
	if( obj->short()!=me->query_temp("pendding/jjf_name") )
	{
		EMOTE_D->do_emote(this_object(), "shake",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+name()+CYN"说道：我要的是"+me->query_temp("pendding/jjf_name")+CYN"，你却给我"+obj->short()+CYN"，这，这。。。。\n"NOR);
		return 0;
	}
	me->delete_temp("pendding/jjf_name");
	EMOTE_D->do_emote(this_object(), "great",geteuid(me),CYN,0,0,0);
	me->set_temp("pendding/jjf_class",1);
	tell_object(me,CYN+name()+CYN"说道：不错不错。\n"NOR);
	tell_object(me,HIC"恭喜！你通过了 将军府 的入门试炼。\n"NOR);
	tell_object(me,HIR"注意：门派试炼任务记录下线会自动清除。\n"NOR);
	tell_object(me,HIC"你现在可以拜入将军府了。\n"NOR);
	return 1;
}