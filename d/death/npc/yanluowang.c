#include <ansi.h>
inherit "/d/dntg/hell/wang.c";
inherit F_MASTER;

int work_me();
string expell_me(object me);
string check_book();
int zhua_gui();
string ask_cancel();

void create()
{
	set_name("阎罗王", ({"yanluo wang","wang", "master", "yanluo"}));
	set_level(159);
	set("long", "身穿大红蟒袍，头戴黑绸软巾．
面如锅底，须若钢针，这就是阎罗王．\n");
	create_family("阎罗地府", 2, "你好");
	set("title", "阴间十王之");
 	set("class", "youling");
	set("gender", "男性");
	set("age", 50);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("force_factor", 60);
	set("mana_factor", 50);

 	set_skill("jinghun-zhang", 1500);
 	set_skill("tonsillit", 1500);
 	set_skill("gouhunshu", 1500);
	set_skill("unarmed", 1500);
 	set_skill("whip", 1480);
 	set_skill("sword", 1500);
 	set_skill("hellfire-whip",1480);
 	set_skill("zhuihun-sword", 1500);
	set_skill("dodge", 1200);
 	set_skill("ghost-steps", 1500);
	set_skill("parry", 1500);
 	set_skill("spells", 1500);
 	set_skill("force", 1500);
        map_skill("sword", "hellfire-whip");
        map_skill("parry", "zhuihun-sword");
        map_skill("dodge", "ghost-steps");
        map_skill("unarmed", "jinghun-zhang");
        map_skill("force", "tonsillit");
        map_skill("whip", "hellfire-whip");
        map_skill("spells", "gouhunshu");

 	set("nk_gain", 500);
 	set("chat_chance_combat", 40);
 	set("chat_msg_combat", ({
                (: exert_function, "sheqi" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: cast_spell, "gouhun" :)
        }) );
	set("inquiry", ([
		"核对生死簿" : (: check_book :),
		"十八层地狱":(: work_me :),
		"18": (: work_me :),
		"灵台观礼": "哦，这个自由地藏王菩萨做主！\n",
		"name": "哼！连老夫都不认得，想来是活的太久了！\n",
		"here": "这便是阎罗地府，到阳间一谈，嘿嘿，没人不怕！\n",
		"阳间": "人说阴阳殊途，其实不然，阴阳间有五点相交，来去相通！\n",
		"五点": "哈哈，要说知道的人却也不多，那便是年，月，日，时和长安泾水桥！\n",
	]) );
	setup();
        carry_object("/d/obj/cloth/mangpao")->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"shoes",1)->wear();
        carry_object(0,"whip",1)->wield();
        powerup(0,1);
}

void attempt_apprentice()
{	
	object me;
	me = this_player();
	
        if( me->query_level()<80 )
        {
                EMOTE_D->do_emote(this_object(), "sigh",geteuid(me),CYN,0,0,0);
                tell_object(me,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(me)+"还是先去找黑白无常打好基础再来。\n");
                return ;
        }
        if( me->query("class")!="ghost" )
        {
        	if( !me->query_temp("pendding/hell_class") ) 
        	{
                	EMOTE_D->do_emote(this_object(), "shake",geteuid(me),CYN,0,0,0);
                	tell_object(me,CYN+name()+CYN"说道：吾等不收外门弟子，汝若诚心想入我门，那就先帮我核对生死簿。\n"NOR);
                	return ;
                }
        }
        EMOTE_D->do_emote(this_object(), "pat",geteuid(me),CYN,0,0,0);
        tell_object(me,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(me) +"多加努力，把我们地府发扬光大。\n"NOR);
        command("recruit " + geteuid(me) );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "ghost");
}

int accept_fight(object me)
{
        command("say " + "哈哈！阎王不叫，自己上门！\n");
        return 1;
}

int regive_all(object who)
{
	int i;
	object *obs,me = this_object();
	
	if( !who ) return 0;
  	obs = all_inventory (who);
  	i = sizeof(obs);

  	message_vision ("满天的乌云渐渐散去。。。。\n",who);
  	while (i--)
  	{
    		object ob = obs[i];
    		if( !ob->query_temp("18break") )
    			continue;
		message_vision ("$N身上$n闪了一闪！\n",who,ob);
		ob->delete_temp("18break");
		ob->delete("breaked");
  	}  
    	return 1;
}

int get_all(object who)
{
	int i;
	object *obs,me = this_object();
	
	if( !who ) return 0;
  	obs = all_inventory (who);
  	i = sizeof(obs);

  	message_vision ("一阵狂风吹来，天地大变，冥冥中有紫雷夹带着狂风出现！\n",who);
  	while (i--)
  	{
    		object ob = obs[i];
    		if( ob->query("breaked") )
    			continue;
    		if( !ob->is_armor() && !ob->is_weapon() && !ob->is_fabao() )
    			continue;	
		message_vision ("一道惊雷闪过，$N身上的$n顿时灵气全无！\n",who,ob);
		ob->unequip();
		ob->set_temp("18break",1);
		ob->set("breaked",1);
  	} 
  	who->reset_action(); 
    	return 1;
}

int work_me()
{
        object who;
        who=this_player();

        if( (int)who->query("daoxing")<175000 )
        {
                message_vision("$N对$n一拱手，道：道行不够，强求亦是枉然。\n", this_object(),who);
                message_vision("$N说道：道行都没到"+RANK_D->describe_dx(175000)+"的境地，进去也是送死。\n",this_object());
                return 1;
        }
        if( who->query("mark/18diyu") && who->query("fangcun/panlong_hell_18")!="begin") 
        {
		message_vision("$N对$n一拱手，道：即是武功高强，我等佩服便是，这。。。便是免了吧！\n",this_object(),who);
		if( !who->is_titles("洗心革面") )
		{
			if( who->set_titles("洗心革面") )
			{
				tell_object(who,HIC"【系统】你获得了称号：「"HIC"洗心革面"NOR HIC"」。\n"NOR);
				CHANNEL_D->do_channel(this_object(),"chat",who->query("name")+"获得了称号：「"HIW"洗心革面" HIC"」。"NOR);
			}
		}
        	return 1;
        }
        if( this_object()->query_temp("SomeonePassing") ) 
        {
                message_vision("$N对$n一拱手，道：真时机缘不巧，改日再来吧。\n",this_object(),who);
                return 1;
        }
        if( time()<who->query("mark/18diyu_fail")+3600 )
        {
                message_vision("$N对$n一拱手，道：修行不够，强求亦是枉然。\n", this_object(),who);
                message_vision("$N说道：你刚刚失败过，还是先去练练！\n",this_object());
                return 1;
        }
	message_vision("$N对$n阴阴地笑了几声，说：天堂有路你不走，地狱无门你闯进来。\n",this_object(),who);
        this_object()->set_temp("SomeonePassing");
        CHANNEL_D->do_channel(this_object(),"chat",who->query("name")+"要闯俺地府十八层地狱，哼！等着收尸吧！");
        message_vision("$N双手拍了一下，$n脚下突然陷了下去。。。\n", this_object(),who);
        who->delete("env/brief_message");
        who->move("/d/death/emptyroom");
        EMOTE_D->do_emote(this_object(), "grin",0,CYN,0,0,0);
        this_object()->set_temp("no_ruturn",1);
        this_object()->move("/d/death/emptyroom");
	call_out("get_all",1,who);
        call_out("message",3,who);
        call_out("round_diyu",4, who,1);
        return 1;
}

int check_status(object who)
{
	if( !who )
		return 0;
	if( (int)who->query("kee") < 50 
         || (int)who->query("eff_kee") < 50
         || !present(who,environment()) )
        {
		remove_call_out("round_diyu");
		remove_call_out("message");
        	remove_call_out("winning");
        	remove_call_out("failed");
		who->set("eff_kee",50);
                call_out("failed",1,who);
                return 1;
        }
}

int failed(object who)
{       
	if( who )
	{
        	command("chat* 狂笑了几声。");
        	CHANNEL_D->do_channel(this_object(),"chat","果真有不怕死的，可惜还是逃不出俺的手掌心！");
        	this_object()->delete_temp("SomeonePassing");
        	who->set("mark/18diyu_fail",time());
        	regive_all(who);
        	who->move("obj/void");
        	who->unconcious();
        	this_object()->set_temp("no_ruturn",0);
        	this_object()->move("/d/death/zhengtang");
        }	
        remove_call_out("remove_all");
        call_out("remove_all", 3);
        return 1;
}

int remove_all()
{
	int i;
        object *list,empty;

        remove_call_out("remove_all");
        if( !(empty = find_object("/d/death/emptyroom")) )
                empty = load_object("/d/death/emptyroom");
        write("四周刮起一阵阴风。。。\n");
        if( empty = find_object("/d/death/emptyroom") ) {

                list=all_inventory(empty);
                i = sizeof(list);
                while (i--)
                {
                        object ob=list[i];
                        ob->move("/d/changan/fendui");
                }
        }
        return 1;
}

int winning(object who)
{
	if( who )
	{	
		regive_all(who);
     		if( who->query("fangcun/panlong_hell_18")=="begin" )
		{
			CHANNEL_D->do_channel(this_object(),"chat",who->query("name")+"，竟然闯过了我幽冥地府十八层地狱！");
			who->set("fangcun/panlong_hell_18","done");
			this_object()->set_temp("no_ruturn",0);
        		this_object()->move("/d/death/zhengtang");
        		this_object()->delete_temp("SomeonePassing");
	        	remove_call_out("remove_all");
        		call_out("remove_all", 3);
        		return 1;
		}
        	CHANNEL_D->do_channel(this_object(),"chat",who->query("name")+"，算你走运，下回可没这么便宜了！");
	        who->add("kar", 10);
        	who->add("potential", 1000);
        	who->add("daoxing", 5000);
        	tell_object(who,"你得到了一千点潜能和五年道行。\n");
        	who->set("mark/18diyu",1);
        	if( who->set_titles("洗心革面") )
        	{
	 		tell_object(who,HIC"【系统】你获得了称号：「"HIC"洗心革面"NOR HIC"」。\n"NOR);
	 		CHANNEL_D->do_channel(this_object(),"chat",who->query("name")+"获得了称号：「"HIW"洗心革面" HIC"」。"NOR);
	 	}
 		who->save();
        }	
        this_object()->move("/d/death/zhengtang");
        this_object()->delete_temp("SomeonePassing");
        remove_call_out("remove_all");
        call_out("remove_all", 3);
        return 1;
}

int message(object who)
{
        remove_call_out("message");
        if( !who )
        	return 0;
        switch(random(5)) 
        {
		case 0: tell_room(environment(who),"\n你觉得自己不断下降，周围景物如彩蝶翻飞，不可注目。\n");break;
                case 1: tell_room(environment(who),"\n你觉得自己不断下降。\n");break;
                case 2: tell_room(environment(who),"\n你觉得自己不断下降，天地似乎没了界限。。。\n");break;
                case 3: tell_room(environment(who),"\n你觉得自己不断下降，周围一切都在旋转。。。\n");break;
                case 4: tell_room(environment(who),"\n你觉得自己不断下降，下降，似乎落向了无尽的深渊。\n");break;
        }
        return 1;
}

string diyu_short(int lvl)
{
	string arg,color,*clr,*name = ({
		"吊筋","幽枉","火坊","酆都","拔舌","剥皮",
		"磨涯","锥捣","车崩","寒冰","脱壳","抽肠",
		"油锅","黑暗","刀山","血池","阿鼻","秤杆",
	});	
	if( lvl<1 || lvl>18 )
		return 0;
	clr = ({RED,YEL,BLU,HIB,MAG,CYN,HIR,HIG,HIY,HIB,HIM,HIC,HIW,});
	arg = "                %s                                    \n"NOR"                %s               %6s%s               \n"NOR"                %s                                    \n"NOR;
	color = clr[random(sizeof(clr))];
	arg = sprintf(arg,NOR+REV+color,NOR+REV+color,NOR REV HIR+name[lvl-1]+"狱"NOR,NOR+REV+color,NOR+REV+color);
	return arg;
}

int round_diyu(object who,int lvl)
{
	int num;
        object ghost;
 	seteuid(getuid());
 	if( who )
 	{
	        tell_room(environment(who),"\n突然间一道黑牌闪过：\n\n");
        	tell_room(environment(who),diyu_short(lvl));
	        ghost=new(__DIR__"gui");
        	ghost->set_level(ghost->query_level()+lvl);
        	ghost->move(environment(who));
        	ghost->invocation(who);
        }
        num = lvl/3;
        if( random(num)>0 )
        {
	        ghost=new(__DIR__"gui");
        	ghost->set_level(ghost->query_level()+lvl);
        	ghost->move(environment(who));
        	ghost->invocation(who);
        }	
        if( who )
        {
		if( lvl==18 )
		{
        		remove_call_out("winning");
			call_out("winning",4,who);
		}
        	else
        	{
        		remove_call_out("message");
        		remove_call_out("round_diyu");
        		call_out("message",3,who);
        		call_out("round_diyu", 4, who,lvl+1);
        	}	
	        remove_call_out("check_status");
		call_out("check_status",1,who);        
        }	
        return 1;
}


string check_book()
{
	object me=this_player();

	if(me->query("family/family_name")=="阎罗地府")
      		return ("你还是安心下去修炼吧！");
      	if( me->query("family/family_name") )
      		return "这位"+RANK_D->query_respect(me)+"说笑了，我阴曹地府可不敢夺"+me->query("family/family_name")+"所好！";	
      	if(me->is_busy())
      		return ("你正忙着呢！");
	if( me->query_level()<40 )
		return "你只管下去找那黑白无常即是。";      		
   	if( me->query_temp("pendding/hell_class") )
      		return "哈哈，事不宜迟，欢迎这位"+RANK_D->query_respect(me)+"加入我阎罗地府。";
	if( (me->query("potential")-me->query("learned_points"))<100 )
		return "你潜能不够，难以沉下心来。";
	if( me->query("sen")<50 )
		return "看你心神不灵，还是下去歇息吧。";	
   	command("say 这儿有一卷生死簿可能有误，你去替我核对一下。");
    	message_vision("$N在桌子旁坐下，聚精会神地进行核对。\n",me);
    	me->add("potential",-100);
   	me->start_busy(5);
   	remove_call_out("finish_check_book");
   	call_out("finish_check_book",5,me,this_object());
   	command("nod");
   	return ("果然是一个勤快人。");
}

void finish_check_book(object me,object master)
{
	int kar;
	kar = me->query_kar();
	remove_call_out("finish_check_book");
    	message_vision("$N查了许久，终于将一卷生死簿查完了，松了一口气，只觉得双眼发酸！\n");
    	me->receive_damage("sen",50);
    	message_vision("$N走到阎罗王面前，恭恭敬敬地说了声：禀告王爷，查完了，没错！\n",me);
    	message_vision("阎罗王低头看了看。\n",me);
    	kar = 150-kar;
    	if( kar<1 ) kar = 1;
    	if( random(150)>kar )
    	{
    		EMOTE_D->do_emote(this_object(), "pat",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(me)+"看来果然与我阴曹地府有缘。\n"NOR);
		me->set_temp("pendding/hell_class",1);
		tell_object(me,HIC"恭喜！你通过了 阎罗地府 的入门试炼。\n"NOR);
		tell_object(me,HIR"注意：门派试炼任务记录下线会自动清除。\n"NOR);
		tell_object(me,HIC"你现在可以拜入地府了。\n"NOR);
	}
	EMOTE_D->do_emote(this_object(), "hmm",geteuid(me),CYN,0,0,0);
	message_vision("阎罗王遗憾的说道：这位"+RANK_D->query_respect(me)+"看来还是未洞察我阴曹的玄机。\n",me);
}
