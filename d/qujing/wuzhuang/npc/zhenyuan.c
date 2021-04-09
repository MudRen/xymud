#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

string begin_go();

void create()
{
   set_name("镇元大仙", ({"zhenyuan daxian", "zhenyuan", "daxian"}));
   set_level(160);
   set("title", "五庄观观主");
   set("gender", "男性" );
   set("age", 65);
   set("long", "交游遍三界，桃李漫五行。好一位地仙之祖！\n");
   set("class", "xian");
   set("attitude", "peaceful");
   create_family("五庄观", 1, "祖师");
   set("rank_info/respect", "观主");
   set_skill("unarmed", 1580);
   set_skill("wuxing-quan", 1600);
   set_skill("dodge", 1580);
   set_skill("baguazhen", 1600);
   set_skill("parry", 1580);
   set_skill("sword", 1580);
   set_skill("sanqing-jian", 1590);
   set_skill("staff", 1600);
   set_skill("fumo-zhang", 1590);
   set_skill("hammer", 1600);
   set_skill("kaishan-chui", 1590);
   set_skill("blade", 1600);
   set_skill("yange-blade", 1590);
   set_skill("force", 1580);   
   set_skill("zhenyuan-force", 1580);
   set_skill("literate", 1580);
   set_skill("spells", 1600);
   set_skill("taiyi", 1600);
   map_skill("spells", "taiyi");
   map_skill("force", "zhenyuan-force");
   map_skill("unarmed", "wuxing-quan");
   map_skill("sword", "sanqing-jian");
   map_skill("dodge", "baguazhen");
   map_skill("staff", "fumo-zhang");
   map_skill("blade", "yange-blade");
   map_skill("hammer", "kaishan-chui");

   set("force_factor", 200);
   set("mana_factor", 200);

   set("inquiry", ([
   	"灵台观礼": (: begin_go :),
   ]));		
   setup();
   carry_object("/d/obj/cloth/xianpao")->wear();
   carry_object("/d/obj/weapon/sword/ruler")->wield();
}

void go_back()
{
	remove_call_out("go_back");
	if( !environment() )
		return;
	if( base_name(environment())=="/d/qujing/wuzhuang/chengyun" )
		return;
	message_vision("\n"HIC"镇元大仙道：观礼事毕，贫道这就回转西牛贺州五庄观，老祖所议之事，容某考虑考虑。\n"NOR,this_object());
        message_vision(HIB"$N"HIB"大袖一摆，平地起身，只见风起云涌，$P在空中连踏出乾坤八位，几步踏出，身形已然消失……\n"NOR,this_object());
	delete_temp("no_return");
	this_object()->move("/d/qujing/wuzhuang/chengyun");
	message_vision(HIB"\n一阵清风吹来，$N"HIB"从空中降落…… \n"NOR,this_object());			
}

string begin_go()
{
	object bagua,me,ob;
	string str;
	int dx,wx,qn,i;
    	
    	me=this_player();
	ob=this_object();
	
	if( !me->query_temp("pendding/fc_visite")
    	 || me->is_knowing("puti_panlong") )
    		return 0;
    	if( base_name(environment())!="/d/qujing/wuzhuang/chengyun" )
    		return "此事待贫道回观后再议。";
	if( me->query_temp("pendding/fc_visite_wzg") )
	{
        	message_vision("\n"HIC"镇元大仙道：" + RANK_D->query_respect(me) + "，贫道即刻赴灵台之约！\n"NOR,me);
        	message_vision(HIB"$N"HIB"大袖一摆，平地起身，只见风起云涌，$P在空中连踏出乾坤八位，几步踏出，身形已然消失……\n"NOR,ob);
        	ob->set_temp("no_return",1);
    		ob->move("/d/lingtai/inside1");
    		message_vision(HIB"\n一阵清风吹来，$N"HIB"从空中降落…… \n"NOR,ob);
		remove_call_out("go_back");
    		call_out("go_back",2700);
		return "贫道与老祖正好有事相商。";
	}
	if( !me->query_temp("pendding/fc_visite_baxianguohai") )
	{
		if( time()<me->query("family/guanli_baxian_fail")+3600 )
			return "唉，那几个徒孙惹下如此祸端，还是缓缓再议吧。";
		if( me->query_temp("pendding/fc_wzgask")<8 )
		{
			if( !me->query_temp("pendding/wzg_askob") )
			{
				bagua = new("/quest/family/wzg/bagua");
				me->set_temp("pendding/wzg_askob",bagua);
				bagua->move(me);
				message_vision("$N交给$n一个铁八卦。\n",ob,me);
			}
			str = "......\n镇元大仙说道："+RANK_D->query_respect(me) + "来的正好，我那八个徒孙近日来不知怎么，心事重重。我平日里管教又严几个小家伙都不敢说实话，" + RANK_D->query_respect(me) + "正好凭信物帮老夫去打听打听他们有什么烦恼。\n";
			str = sort_msg(str);
			return str;
		}
		if( me->query_temp("pendding/wzg_askob") )
			destruct(me->query_temp("pendding/wzg_askob"));
		if( !me->query_temp("pendding/fc_visite_seask") )
		{	
			tell_object(me,"\n你上前将事情原委朝镇元大仙讲了一遍。\n");
			tell_object(me,name()+"点了点头，低头掐指一算。\n");
			EMOTE_D->do_emote(this_object(), "ah",0,CYN,0,0,0);
			return "几位徒孙近日东海一游，恐生祸端，烦请"+RANK_D->query_respect(me)+"代贫道前去东海龙宫探个究竟。";
		}	
		str = CYN+name()+"说道：呵呵，是祸躲不过，既然如此，就随他们去吧。烦请"+RANK_D->query_respect(me)+"也随他们去，若有事情，也好从中调停。\n"NOR;
		str = sort_msg(str);
		tell_object(me,str);
		return RANK_D->query_respect(me)+"准备好了，贫道便送(song)你去。";
	}
	me->set_temp("pendding/fc_visite_wzg",1);
	if( me->query_temp("pendding/fc_visite_sea") )
		me->delete_temp("pendding/fc_visite_baxianguohai");
	me->delete_temp("pendding/wzg_baxian1");
	me->delete_temp("pendding/wzg_baxian2");
	me->delete_temp("pendding/wzg_baxian3");
	me->delete_temp("pendding/wzg_baxian4");
	me->delete_temp("pendding/wzg_baxian5");
	me->delete_temp("pendding/wzg_baxian6");
	me->delete_temp("pendding/wzg_baxian7");
	me->delete_temp("pendding/wzg_baxian8");
	me->add_temp("pendding/fc_visited",1);
	CHANNEL_D->do_channel(this_object(),"chat",HIY+me->name()+HIC"助我调停「八仙闹东海」一事,届时贫道一定上灵台观礼！"NOR);
	if( !me->query("mark/guanli_wzg") )
	{
		dx = ((me->query("daoxing")/1000)/10+1)*1000;
		if( dx>=81000) 
			dx = 81000;
		wx = dx+random(dx);	
		qn = 10000;
		me->add("daoxing",dx);
		me->add("combat_exp",wx);
		me->add("potential",qn);
		tell_object(me,HIY"【灵台观礼】你得到了"+wx+"点武学经验、"+chinese_number(dx/1000)+"年道行以及"+qn+"点潜能的奖励！\n"NOR);
		me->set("mark/guanli_wzg",1);
	}	
	tell_object(me,HIY"【灵台观礼】你已成功邀请到"+chinese_number(me->query_temp("pendding/fc_visited"))+"位圣贤参加灵台观礼。\n"NOR);
	if( me->query("family/family_name")=="方寸山三星洞")
		return "观礼之日还请" + RANK_D->query_respect(me) + "再来告知一声。";
	else	return "多谢多谢。";	
}

void die()
{
	if( environment() )
		message("vision","\n\n"+name()+"哈哈一笑，纵身化作一道金光冲天而去。\n\n",environment());
	destruct(this_object());
}

void init()
{
	add_action("do_song","song");
}

int do_song()
{
	object room,xian,me = this_player();
	if( !me->query_temp("pendding/fc_visite_seask") )
		return 0;
	if( !me->query_temp("pendding/fc_visite")
    	 || me->is_knowing("puti_panlong") )
    	 	return 0;
    	if( me->query_temp("pendding/fc_visite_wzg") )
    		return 0;
	
	room = clone_object("/quest/family/wzg/sea1");
	room->set("owner",me);
	
	tell_object(me,"\n镇元大仙朝了挥了挥衣袖，你眼前一黑。。。。\n\n");
	me->move(room);
	tell_object(me,"\n\n眨眼间你已来到了东海之滨。\n");
	room->start_story(me,1);
	return 1;
}