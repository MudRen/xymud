//40突破
#include <ansi.h>

void get_input(string arg, object me)
{
	string file,old_color,fam,title,str;
	object obj,npc;
	int now,need,max,old_armor;

	if( !me || !environment(me) || !objectp(npc=me->query_temp("pending/zhuji_ask")) )
		return;
	if( !stringp(fam=npc->query("family/family_name"))
	 || me->query("family/family_name")!=fam )
	{
		tell_object(me,CYN+npc->name()+CYN"疑惑的看着你。\n"NOR);
		return;
	}	
	if( interactive(npc) )
	{
		tell_object(me,CYN+npc->name()+CYN"诚惶诚恐的看着你。\n"NOR);
		return;
	}	
	if( npc->is_fighting() || npc->is_busy() || !living(npc) )
	{
		tell_object(me,"对方现在无法回应你。\n");		
		return;
	}
	if( ( me->query_level()!=39||me->query("combat_exp")<16100000 )
	 && !wizardp(me) )
		return;
        if( me->query("mark/40tupo111") )
		return;

	if( !arg )
	{
		tell_object(me,HIY"你要选择哪种途径来"HIC"筑基"HIY"，按"HIR"Q"HIY"退出选择 (1. 通过筑基丹 2. 去找五行灵物)"NOR);
		input_to("get_input",me);
		return;
	}
	if( arg[0..0]=="Q" || arg[0..0]=="q" )
		return;
	if( arg[0..0]=="1" )
	{
		if( me->query("faith")<200000 && !wizardp(me) )
		{
			tell_object(me,CYN+npc->name()+CYN"朝你瞥了一眼：本派的"NOR HIC"筑基丹"NOR CYN"也不是大白菜，需要二十万门派贡献兑换。\n"NOR);
			tell_object(me,CYN+npc->name()+CYN"说道：别整天怨天尤人，你自己也得出力！且下去多为门派做贡献，到时再来找我。\n"NOR);
			return;
		}
		me->add("faith",-200000);
		message_vision("$N思来想去，还是觉得吃药保险，对$n说道：给我"HIC"筑基丹"NOR"吧。\n",me,npc);
		EMOTE_D->do_emote(npc, "nod",geteuid(me),CYN,0,0,0);
		message_vision(HIC"\n$n"HIC"去房中片刻后，手拿一枚异香扑鼻的药丸出来，对$N"HIC"说道：便在此地食用，吾也好替你护法。\n\n"NOR,me,npc);
		tell_object(me,HIY"【系统】你得到了一枚"HIC"筑基丹"HIY"。\n"NOR);
		CHANNEL_D->do_channel(npc,"rumor","听说"+me->name()+HIM"得到了"+fam+"炼制的"HIC"筑基丹"HIM"！"NOR);
		message_vision(HIR"$N"HIR"将一仰脖，囫囵将"HIC"筑基丹"HIR"吞了下去，立即觉得体力法力沸腾，慌忙坐地运功吸收药中精华。\n"NOR,me);
		if( me->query_level()==39 || (wizardp(me)&&me->query("env/test")) )
		{
			if( me->level_up() )
			{
				tell_object(me,HIG"【系统】你的等级提升了"HIR"1"HIG"级。\n"NOR);
				CHAR_D->setup_char( me );
				UPDATE_D->check_user(me,1);
				me->powerup(0,1);
				me->set_temp("login_data/time", time());
				me->set_temp("login_data/exp", 0);
				me->add("max_gin",500);
				me->save();
			}
			else	tell_object(me,HIR"【系统】升级失败，赶紧联系巫师。\n"NOR);
		}
		return;
	}
	else if( arg[0..0]=="2" )
	{
		EMOTE_D->do_emote(npc, "nod",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+npc->name()+CYN"说道：不错不错，你是个有大毅力的人呐。吾道不孤。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：五行之极金之地在蜀山的"NOR HIY"销金窝"NOR CYN"。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：五行之极木之地在月宫的"NOR HIG"建木遗迹"NOR CYN"。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：五行之极水之地在雪山的"NOR HIW"雪山寒林"NOR CYN"。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：五行之极火之地在高老庄的"NOR HIR"星石巨坑"NOR CYN"。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：五行之极土之地在终南山的"NOR HIC"终南幽谷"NOR CYN"。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：此五处你任选一处前去，打得五行精华给我即是。\n"NOR);
		me->set_temp("maze/40tupo",1);
		return;
	}
	else
	{
		tell_object(me,HIY"你要选择哪种途径来"HIC"筑基"HIY"，按"HIR"Q"HIY"退出选择 (1. 通过筑基丹 2. 去找五行灵物)"NOR);
		input_to("get_input",me);
		return;
	}
}

mixed ask_zhuji(object me,object npc)
{
	string fam,str;
	if( !interactive(me) )
		return 0;
	if( !stringp(fam=npc->query("family/family_name"))
	 || me->query("family/family_name")!=fam )
	 	return 0;	
	if( ((me->query_level()==39&&me->query("combat_exp")>=16100000)
	 ||wizardp(me)) )
	{
                if( me->query("mark/40tupo111") )
			return "不错不错，来来来，将此次收获给"+RANK_D->query_self(npc)+"看看。";
		me->set_temp("pending/zhuji_ask",npc);	
		EMOTE_D->do_emote(npc, "great",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+npc->name()+CYN"说道：既然你已修炼至炼气大圆满，那"+RANK_D->query_self(npc)+"便将筑基一事说与你知。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：筑基有两种途径，一是以各门派炼制的筑基丹来突破修炼瓶颈。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：第二种办法是以五行精华做筑基导引，通过吸取五行精华来突破修炼瓶颈。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：前者虽然成功率较高，但因靠药力所致，故突破后将不能领悟小神通。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：后者虽有失败可能，但对自身却也是一种修炼，在突破的过程中，将会领悟五行中的精华而得到一门小神通(cast xiaoshen)。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道："+me->query("name")+"，你考虑下用什么途径来突破？\n"NOR);
		tell_object(me,HIY"你要选择哪种途径来"HIC"筑基"HIY"，按"HIR"Q"HIY"退出选择 (1. 通过筑基丹 2. 去找五行灵物)"NOR);
		input_to("get_input",me);
		return "我很欣慰。";
	}	 
	else if( me->query_level()>39 )
		return "你是麻黄散吃多了吧？！";
	else	return "言之尚早。";
}	

mixed give_zhuji(object me,object npc,object ob)
{
	int wxs,wxlvl,succ;
	string file,fam,str,wx,wx_type,msg;
	
	if( !interactive(me) )
		return 0;
	if( !stringp(fam=npc->query("family/family_name"))
	 || me->query("family/family_name")!=fam )
	 	return 0;	
	if( !me->query("mark/40tupo") || !ob )
		return 0;
///d/maze/tupo40-1/obj/max  /d/maze/tupo40-2/obj/yang6
	if( strsrch(base_name(ob),"/d/maze/tupo40-")==-1 )
		return 0;
	if( ((me->query_level()==39&&me->query("combat_exp")>=16100000)
	 ||wizardp(me)) )
	{
		file = base_name(ob);
		if( sscanf(file,"/d/maze/tupo40-%d/obj/%s",wxs,file)!=2 )
			return 0;
		switch(wxs)
		{
			case 1 : wx="金";break;
			case 2 : wx="木";break;
			case 3 : wx="水";break;
			case 4 : wx="火";break;
			case 5 : wx="土";break;
			default : return 0;
		}	
		if( file=="max" )
		{
			wxlvl = 7;
			wx_type = "阳";
		}
		else
		{
			if( sscanf(file,"%s%d",wx_type,wxlvl)!=2 )
				return 0;
			if( wx_type=="yang" )
				wx_type = "阳";
			else	wx_type = "阴";
		}
		
		EMOTE_D->do_emote(npc, "zeze",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+npc->name()+CYN"说道：不错不错，此乃"+chinese_number(wxlvl)+"级"+wx_type+wx+"之精。\n"NOR);
		tell_object(me,CYN+npc->name()+CYN"说道：来来来，这就以此为介，搭天地之桥，冲级瓶颈！。\n"NOR);
		if( !npc->query("class") )
			msg = "手印";
		else if( npc->query("class")=="yaomo" )
			msg = "上古妖印";
		else if( npc->query("class")=="bonze" )
			msg = "佛印";
		else	msg = "道印";			
		message_vision(HIC"$N"HIC"盘膝坐下，$n"HIC"站在其身后，一手结"+msg+"，一手将"+ob->name()+HIC"至于$P泥丸宫之上，口中念叨了几句咒语。\n"NOR,me,npc);
		message_vision(HIC"顿时霞光万丈，异象纷纭，"+ob->name()+HIC"之上"+wx+"之精华源源不断进去了$N"HIC"体内。\n"NOR,me);
		succ = random(10);
		if( succ>5 || me->query("mark/40fail")>=3 )
		{
			me->delete("mark/40tupo");
			me->delete("mark/40fail");
			if( !me->query("shentong/40") )
				me->set("shentong/40",wx+"_"+wx_type+"_"+wxlvl);
			if( random(2) && !wizardp(me) )
				EMOTE_D->do_emote(npc, "haha",0,CYN,0,0,0);
			else	npc->command("chat* gongxi");
			if( !me->query("class") )
				msg = "筑基";
			else if( me->query("class")=="yaomo" )
				msg = "聚灵";
			else if( me->query("class")=="bonze" )
				msg = "聚元";
			else if( me->query("class")=="ghost" )
				msg = "灵动";
			else	msg = "筑基";	
			if( me->level_up() )
			{
				tell_object(me,HIG"【系统】你的等级提升了"HIR"1"HIG"级。\n"NOR);
				CHAR_D->setup_char( me );
				UPDATE_D->check_user(me,1);
				me->powerup(0,1);
				me->set_temp("login_data/time", time());
				me->set_temp("login_data/exp", 0);
				me->add("max_gin",600);
				me->save();
			}
			CHANNEL_D->do_channel(npc,"chat","呵呵，我"HIY+fam+HIC"弟子"+me->name(1)+HIC"今日突破成功，成功到达 "HIR+msg+HIC" 的境界，真乃师门幸事。"NOR);
			return 2;
		}
		else
		{
                        me->add("mark/40fail",1);
			me->delete("mark/40tupo");
			message_vision(HIR"结果$N"HIR"心神一阵不宁，冲瓶颈失败了！\n"NOR,me);
			EMOTE_D->do_emote(npc, "sigh",geteuid(me),CYN,0,0,0);
			tell_object(me,CYN+npc->name()+CYN"说道：你也莫灰心，仙路如登天，再接再厉，自当成功。\n"NOR);
			tell_object(me,CYN+npc->name()+CYN"说道：何况以五行之灵冲顶筑基，自古有逢三必成的说法。\n"NOR);
			return 2;
		}
	}	 
	else	return 0;
}
