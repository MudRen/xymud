//modified by vikee for xlqy for NK_DX
//2000-11-23 16:18

inherit NPC;
string send_me(object me);
void create()
{
        set_name("魔礼青", ({ "moli qing", "zengzhang tianwang", "qing", "tianwang" }) );
        set("gender", "男性" );
	set("long",
		"增长天王为四大天王之首, 身高二丈四尺, 善用一杆长枪, \n"
		"枪法登峰造极, 更有密传「青云宝剑」, 「地，水，火，风」\n"
		"四式一出, 大罗金仙也难逃。\n"
	);
	set("age",50);
	set("title", "增长天王");
	set("attitude", "heroism");
	set_level(140);
        set("daoxing",3000000);
	set("force_factor", 120);
	set("mana_factor",120);
	
        set("eff_dx", 1500000);
        set("nkgain", 800);

	set_skill("unarmed",1400);
	set_skill("yingzhaogong", 1400);
	set_skill("parry",1400);
	set_skill("dodge",1400);
	set_skill("spear",1400);
	set_skill("bawang-qiang",1400);
	set_skill("force",1400);
	set_skill("spells", 1400);
	set_skill("moshenbu", 1400);
	map_skill("dodge", "moshenbu");
	map_skill("parry", "bawang-qiang");
	map_skill("spear","bawang-qiang");
	map_skill("unarmed", "yingzhaogong");
	set("inquiry", ([
		"name" : "在下增长天王魔礼青，奉圣谕把守西天门。",
		"here" : "这里就是西天门, 入内就是天界了。",
		"回去": (: send_me :),
		"back": (: send_me:),
	]) );

	setup();
	set_temp("armor_level",100);
	set_temp("weapon_level",100);
	setup();
	carry_object(0,"spear",random(10))->wield();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
}


string send_me(object me)
{
        me=this_player();
	        if( me->is_fighting() )
		return ("刚来就惹麻烦，鬼才要理你！\n");
        if( me->is_busy() || me->query_temp("pending/exercising"))
		return ("忙完再说吧。。。\n");

	message_vision("增长天王哈哈大笑，对$N说道：本王这就送你回去！\n", me);
	message_vision("增长天王飞起一脚把$N踢了下去。。。\n", me);
        me->move("/d/changan/nbridge");
	tell_room( environment(me), "「咕咚」一声，从天上掉下个人来！\n", ({me}));
	write("你从天上摔了下来，搞了个鼻青脸肿！\n");
	return ("老夫脚正痒痒。。。\n");
}

int accept_fight(object me)
{
    object ob=this_object();

    if( living(ob) )
      {
      message_vision("$N说到：也要你知道本天王的厉害！\n", ob);
      }
        return 1;
}

void kill_ob (object me)
{
        object ob=this_object();

    if( living(ob) )
       {
        message_vision("$N说到：送你上西天！\n", ob);
       }

	::kill_ob(me);

}

