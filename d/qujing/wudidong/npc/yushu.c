// yushu.c, 玉鼠精
#include <ansi.h>
inherit SUPER_NPC;

void create()
{
	set_name("玉鼠精", ({"yu shu","yushu", "shu", "monster"}));
  	set_level(169);
  	set("gender", "女性" );
  	set("age", 23);
  	set("long", 
"她就是这无底洞的洞主了。她从修道成人行以来，吃人无数，\n"
"也不知为什么玉皇还未曾派兵来围剿。听说她在天宫有亲，也\n"
"不知真假。\n");
	create_family("陷空山无底洞", 1, "弟子");
  	set("title", "地涌夫人");
  	set("attitude", "heroic");
  	set_skill("unarmed",1690);
  	set_skill("dodge", 1690);
  	set_skill("parry", 1690);
  	set_skill("spells", 1690); 
  	set_skill("yaofa", 1690);
  	set_skill("sword",1690);
  	set_skill("qixiu-jian",1690);
  	set_skill("blade", 1690);
  	set_skill("kugu-blade", 1690);
  	set_skill("lingfu-steps",1690);
  	set_skill("yinfeng-zhua",1690);
  	set_skill("force", 1690);   
  	set_skill("huntian-qigong", 1690);
	set_skill("literate",1690);
  	map_skill("force", "huntian-qigong");
  	map_skill("spells", "yaofa");
  	map_skill("unarmed", "yinfeng-zhua");
  	map_skill("sword", "qixiu-jian");
  	map_skill("parry", "kugu-blade");
  	map_skill("blade", "kugu-blade");
  	map_skill("dodge", "lingfu-steps");
  	
  	set_skill("zhaoyun",1690);
  	set_skill("feisha-zoushi",1690);
  	set_skill("tuxing",1690);
  	set_skill("zhihua",1690);

  	set("force_factor", 150);
  	set("mana_factor", 50);
  	set("inquiry",([
		"name": "老娘就是这无底洞的开山祖师！",
       		"here": "这里就是陷空山无底洞！就算你调十万天兵来也奈何我不得！",
       		"rumors": "老娘刚刚抓住一个和尚。看来马上就有新鲜人肉吃了。",
       		"人肉包子": "混帐！饿了不会去找厨子？",
       		"和尚": "嘿嘿，眼下正饿着他呢。等他肠子干净了就可以蒸熟了吃了。\n不过也该派人去看看他了。说不定他已经饿死了。",
       		"看看": "要看看也行，就是不知道我把钥匙放哪儿了。",
	]));
	set("env/test","HIR");
	set_temp("weapon_level",50+random(50));
	set_temp("armor_level",50+random(50));
  	setup();
  	carry_object(0,"blade",1)->wield();
  	carry_object(0,"cloth",1)->wear();
  	carry_object(0,"shoes",1)->wear();
  	carry_object(0,"neck",1)->wear();
  	carry_object(0,"ring",1)->wear();
  	carry_object(0,"kui",1)->wear();
  	carry_object(0,"pifeng",1)->wear();
  	powerup(0,1);
}

int prevent_learn(object me, string skill)
{
	int mykugu = me->query_skill("kugu-blade", 1);
  	if( wizardp(me) && me->query("env/immortal"))
    		return 0;
  	if( skill == "kugu-blade")
  	{
      		if( mykugu<180)
      		{
   			tell_object(me,CYN+name()+CYN"说道：你难道是来消遣老娘的？\n"NOR);
   			return 1;
      		}
	}
  	return 0;
}

int accept_object(object me, object ob)
{
	int volume;
	if( me->query_level()<125 )
	{
		tell_object(me,CYN+name()+CYN"说道：你这样的修为也好意思做我徒弟？！\n"NOR);
		return 0;
	}
    	if( ob->query("name_recognized") != "枯骨刀秘笈")
    	{
		tell_object(me,CYN+name()+CYN"说道：混帐，我又不是收破烂的！\n"NOR);
		return 0;
	}
	if( !me->query("family/wdd_book_want") )		
	{
		tell_object(me,CYN+name()+CYN"说道：老娘和你不熟！！\n"NOR);
		return 0;
	}
	if( me->query("family/wdd_book_give") )
	{
		tell_object(me,CYN+name()+CYN"说道：不用给了，快来与老娘行拜师之礼！\n"NOR);
		return 0;
	}
    	if( me->query("family/master_id") == "yu shu")
    	{
    		tell_object(me,CYN+name()+CYN"说道：好徒弟，果然不枉了师父的一番调教。"NOR"\n");
    		return 1;
    	}
	volume=ob->query("册");
	if( !me->query("family/wdd_book_"+(string)volume) )
	{
		me->set("family/wdd_book_"+(string)volume, 1);
		me->add("family/wdd_book_n",1);
	}
	if( me->query("family/wdd_book_n")>=4 )	
	{
		tell_object(me,CYN+name()+CYN"说道：嗯，果然不错。老娘自当履行诺言，收你为徒！"NOR"\n");
		EMOTE_D->do_emote(this_object(), "chan",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+name()+CYN"说道：还不来与老娘行拜师之礼？\n"NOR);	
		me->delete("family/wdd_book_1");
		me->delete("family/wdd_book_2");
		me->delete("family/wdd_book_3");
		me->delete("family/wdd_book_4");
		me->set("family/wdd_book_give",1);
		me->delete("family/wdd_book_want");
		me->save(1);
		return 1;
	}
	tell_object(me,CYN+name()+CYN"说道：嗯，果然不错。不过还不够，老娘还要！"NOR"\n");
    	return 1;
}

void attempt_apprentice(object ob)
{
	if( ob->query("class")=="xian" || ob->query("class")=="dragon"
         || ob->query("class")=="bonze" || ob->query("class")=="taoist" )
        {
		EMOTE_D->do_emote(this_object(), "heng",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：你是哪路神仙派来的卧底？！\n"NOR);
           	this_object()->kill_ob(ob);
           	ob->fight_ob(this_object());
           	return ;
        }
        if( ob->query("class")!="yaomo" )
        {
        	if( !ob->query("family/wdd_class") )
        	{
        		EMOTE_D->do_emote(this_object(), "zeze",geteuid(ob),CYN,0,0,0);
           		tell_object(ob,CYN+name()+CYN"说道：想弃暗投明？还是去问过总管吧。\n"NOR);
           		return ;
        	}
        }
        if( ob->query_level()<125 )
        {
		EMOTE_D->do_emote(this_object(), "pei",geteuid(ob),CYN,0,0,0);
           	tell_object(ob,CYN+name()+CYN"说道：下去先练着吧！！\n"NOR);
           	return ;
        }
        if( !ob->query("family/wdd_book_give") )
        {
        	if( ob->query("family/wdd_book_want") )
		{
			EMOTE_D->do_emote(this_object(), "heng",geteuid(ob),CYN,0,0,0);
        	   	tell_object(ob,CYN+name()+CYN"说道：老娘要的书呢？！\n"NOR);
           		return ;
		} 
		else
		{
			ob->set("family/wdd_book_want",1);
			EMOTE_D->do_emote(this_object(), "xixi",geteuid(ob),CYN,0,0,0);
			tell_object(ob,CYN+name()+CYN"说道：你去帮偶找到"NOR HIY"四"NOR CYN"本"NOR YEL"【枯骨刀秘笈】"NOR CYN"，老娘就收了你！"NOR"\n");
			return;
		}       		
        }
	EMOTE_D->do_emote(this_object(), "pat",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们无底洞发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        return;
}

void recruit_apprentice(object ob)
{
  	if( ::recruit_apprentice(ob) )
  	{
		ob->delete("family/wdd_book_1");
		ob->delete("family/wdd_book_2");
		ob->delete("family/wdd_book_3");
		ob->delete("family/wdd_book_4");
		ob->delete("family/wdd_book_give",1);
		ob->delete("family/wdd_book_want");
		ob->set("class", "yaomo");
	}
	return;	
}