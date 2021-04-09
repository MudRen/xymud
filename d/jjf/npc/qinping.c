#include <ansi.h>
inherit F_MASTER;
inherit NPC;

void create()
{
  set_name("秦平", ({"qin ping", "qin", "master"}));
  set_level(20);
  create_family("将军府", 3, "蓝");
  set("title", "将军府管家");
  set("gender", "男性");
  set("age", 46);
  set_skill("spear", 190);
  set_skill("force", 190);
  set_skill("dodge", 190);
  set_skill("parry", 190);
  set_skill("yanxing-steps", 190);
  set_skill("bawang-qiang", 190);
  set_skill("lengquan-force", 190);
  set_skill("unarmed", 190);
  set_skill("changquan", 190);
  map_skill("force", "lengquan-force");
  map_skill("unarmed", "changquan");
  map_skill("spear", "bawang-qiang");
  map_skill("parry", "bawang-qiang");
  map_skill("dodge", "yanxing-steps");
  set("force_factor", 20);
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