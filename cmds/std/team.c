// team.c
#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

void remove_temp(object who)
{
	if( who )
	{
		who->delete_temp("pending/team");
		who->delete_temp("pending/team_to");
	}
}

int team_name(object who,string arg)
{
	object *t;
	int i;
	string name,n;
	if( !pointerp(t = who->query_team()) )
		return notify_fail("你没有组队。\n");
	if( who!=who->query_leader() )
		return notify_fail("你不是队长。\n");	
	name = who->query_team_name();
	if( name && name!="默认组队" )
		return notify_fail("你已设置战队名为："+name+"。\n");	
	name = COLOR_D->replace_color(arg);		
	name = COLOR_D->clean_color(name);	
	if( !LOGIN_D->check_legal_name(name) )
		return 0;
	arg = COLOR_D->replace_color(arg,2);	
	who->set_team_name(arg);
	message("team", HIW"【组队】"+who->name() + HIW"将队伍名称设置为【"NOR+arg+NOR HIW"】。"NOR"\n",t);
	for(i=0;i<sizeof(t);i++)
	{
		if( t[i] && t[i]!=who )
			t[i]->set_team_name(arg);
	}
	return 1;
}

string query_team_hp(object who)
{
	if( !who )
		return "";
	return sprintf(HIG"血 "HIR"%3d%%"HIY"/"HIR"%3-d%%  "HIG"精 "HIR"%3d%%"HIY"/"HIR"%3-d%%"NOR,
			who->query("kee")*100/who->query("eff_kee"),
			who->query("eff_kee")*100/who->query_maxkee(),
			who->query("sen")*100/who->query("eff_sen"),
			who->query("eff_sen")*100/who->query_maxsen(),
			);			
}		

int main(object me, string arg)
{
	object *t,ob,who;
	int i;
	string name,msg,str;

    	if( !arg || arg=="me" || arg==me->query("id") ) 
    	{
		if( !pointerp(t = me->query_team()) )
			return notify_fail("你现在并没有参加任何队伍。\n");
		name = me->query_team_name();
		if( name && name!="默认组队" )	
			str = "\n"REV HIR" "NOR+name+NOR REV HIR" "NOR"\n";
		else	str = "\n"REV HIR" "NOR+"队伍"+NOR REV HIR" "NOR"\n";
                str+= "      "HIC"队长："HIG+( me->query_leader()?(me->query_leader())->short():"" )+NOR"\n";
		str+= "      "HIC"成员："NOR"\n";
		for(i=0;i<sizeof(t);i++)
		{
			if( t[i] )
				str+= sprintf("          "HIC"%2s"HIG"LV"NOR HIY"%3-d"NOR"%20-s %s\n",t[i]==me?"★":"  ",t[i]->query_level(),t[i]->name()+"("+t[i]->parse_command_id_list()[0]+")",query_team_hp(t[i]));
		}
		if( me->team_buff()>0 )
			str+= "组队加成："+(100+me->team_buff())+"%\n";
		me->start_more(str);	
		return 1;
    	}
    	if( sscanf(arg,"name %s",arg)==1 )
    		return team_name(me,arg);
    	if( arg=="dismiss" ) 
    	{
		if( !pointerp(t = me->query_team()) )
			return notify_fail("你现在并没有参加任何队伍。\n");
		if( me->is_team_leader() ) 
		{
			message("team", HIW"【组队】"+me->name(1) + HIW"将队伍解散了。"NOR"\n", t);
	    		write("你将队伍解散了。\n");
		} 
		else 
		{
			message("team", HIW"【组队】"+me->name(1) + HIW"离开了队伍。\n"NOR, t);
	    		write("你脱离了你的队伍。\n");
		}
		me->dismiss_team();
		remove_temp(me);
		return 1;
    	}
    	if( sscanf(arg, "talk* %s", arg)==1 ) 
	{
		string vb, emote_arg;
		if( !pointerp(t=me->query_team()) )
	    		return notify_fail("你现在并没有和别人组成队伍。\n");
        	if( sscanf(arg, "%s %s", vb, emote_arg)!= 2 )
		{
        		vb = arg;
            		emote_arg = "";
        	}
		if (!(msg = EMOTE_D->do_emote(me, vb, emote_arg, 1, 0, 0)))
			return 0;
		message("team", HIW "【队伍】" + msg + NOR, t);
		return 1;
    	}
    	else if( sscanf(arg, "talk %s", arg)==1 ) 
    	{
		if( !pointerp(t=me->query_team()) )
	    		return notify_fail("你现在并没有和别人组成队伍。\n");
		message("team", HIW "【队伍】" + me->name(1) + HIW"：" + arg + "\n" NOR, t);
		return 1;
    	}
    	else if( sscanf(arg, "with %s", arg)!=1 ) 
    	{
    		if( !wizardp(me) )
    			return help(me);
    		if( !(ob = present(arg, environment(me))) )
    			ob = find_living(arg);
    		if( !ob )
    			ob = find_player(arg);
    		if( !ob )
    			return notify_fail("没有"+arg+"这个人。\n");
		if( !pointerp(t = ob->query_team()) )
			return notify_fail(ob->name(1)+"现在并没有参加任何队伍。\n");
		str = ob->name(1)+"现在队伍中的成员有：\n  ";
		for(i=0;i<sizeof(t);i++)
		{
			if( t[i] )
			{
				if( t[i]->is_team_leader() && ob->is_team_leader(t[i]) )
					str+= "\t"+HIG"㊣"NOR+t[i]->short()+"\n";
				else	str+= "\t  "+t[i]->short()+"\n";	
			}
		}
		if( ob->team_buff()>0 )
			str+= "组队加成："+(100+ob->team_buff())+"%\n";
		me->start_more(str);	
		return 1;
    	}		
	if( !(ob = present(arg, environment(me)))
	 || !living(ob)
	 || !ob->is_character()
	 || ob==me )
		return notify_fail("你想和谁成为伙伴？\n");
	if( !pointerp(me->query_team()) )
	{
		if( !pointerp(ob->query_team()) )
		{
			if( ob->query_temp("pending/team")
			 && ob->query_temp("pending/team")==me )
			{
		    		ob->add_team_member(me);
		    		me->set_leader(ob);
		    		ob->set_leader();
		    		t = me->query_team();
		    		message("team", HIW"【组队】"+me->name(1) + HIW"决定加入"+ob->name(1)+HIW"的队伍。\n"NOR, t);
		    		remove_temp(me);
		    		remove_temp(ob);
		    		return 1;
			}
			else if( !me->query_temp("pending/team") )
			{
				tell_object(me,HIW"【组队】你邀请"+ob->name()+HIW"加入队伍。\n"NOR);
				tell_object(ob,HIW"【组队】"+me->name()+HIW"邀请你加入队伍。\n"NOR);
				me->set_temp("pending/team",ob);
				tell_object(ob, YEL "如果你愿意加入，请用 team with " + me->parse_command_id_list()[0] + "。\n" NOR);
				return 1;
			}
			else if( me->query_temp("pending/team")!=ob )
			{
				who = me->query_temp("pending/team");
				if( who )
					tell_object(who,HIW"【组队】"+me->name()+HIW"取消了邀请你加入队伍的意图。\n"NOR);
				tell_object(me,HIW"【组队】你邀请"+ob->name()+HIW"加入队伍。\n"NOR);
				tell_object(ob,HIW"【组队】"+me->name()+HIW"邀请你加入队伍。\n"NOR);
				me->set_temp("pending/team",ob);
				tell_object(ob, YEL "如果你愿意加入，请用 team with " + me->parse_command_id_list()[0] + "。\n" NOR);
				return 1;
			}
			else	return notify_fail("你已经对他发出邀请了。\n");						
		}
		else if( ob!=ob->query_leader() )
		{
			if( ob->query_leader() )
				msg = "，你可以向"+sprintf("%s(%s)",(ob->query_leader())->query("name"),capitalize((ob->query_leader())->query("id")))+"提出入队申请。\n";
			else	msg = "。\n";	
			return notify_fail("对方不是队长"+msg);
		}
		else
		{
			if( ob->query_temp("pending/team")
	 		 && ob->query_temp("pending/team")==me )
			{
				me->add_team_member(ob);
				ob->set_leader(me);
				t = me->query_team();
				message("team", HIW"【组队】"+ob->name(1) + HIW"决定加入"+me->name(1)+HIW"的队伍。\n"NOR, t);
				remove_temp(me);
				remove_temp(ob);
				return 1;
			}
			if( !me->query_temp("pending/team_to") )
			{
				tell_object(ob,HIW"【组队】"+me->name()+HIW"申请加入你的队伍。\n"NOR);
				tell_object(ob, YEL "如果你同意，请用 team with " + me->parse_command_id_list()[0] + "。\n" NOR);
				me->set_temp("pending/team_to",ob);
				write("你申请加入"+ob->name()+"的队伍，等待对方加入。\n");
				return 1;
			}
			else if( me->query_temp("pending/team_to")==ob )
				return notify_fail("你已经提出了申请，等待对方的同意。\n");
			else
			{
				who = me->query_temp("pending/team_to");
				if( who )
					tell_object(who,HIW"【组队】"+me->name()+HIW"取消了加入你的队伍的申请。\n"NOR);
				tell_object(ob,HIW"【组队】"+me->name()+HIW"申请加入你的队伍。\n"NOR);
				tell_object(ob, YEL "如果你同意，请用 team with " + me->parse_command_id_list()[0] + "。\n" NOR);
				me->set_temp("pending/team_to",ob);
				write("你申请加入"+ob->name()+"的队伍，等待对方加入。\n");
				return 1;
			}	
		}
	}
	if( me!=me->query_leader() )	
		return notify_fail("只有队长才可以邀请别人加入。\n");	
	if( ob->query_team() ) 
		return notify_fail("对方已经加入了队伍。\n");
	if( ob->query_temp("pending/team")
	 && ob->query_temp("pending/team")==me )
	{
		me->add_team_member(ob);
		ob->set_leader(me);
		t = me->query_team();
		message("team", HIW"【组队】"+ob->name(1) + HIW"决定加入"+me->name(1)+HIW"的队伍。\n"NOR, t);
		remove_temp(me);
		remove_temp(ob);
		return 1;
	}	 	
	if( ob->query_temp("pending/team_to")
	 && ob->query_temp("pending/team_to")==me )
	{
		me->add_team_member(ob);
		ob->set_leader(me);
		t = me->query_team();
		message("team", HIW"【组队】"+me->name(1) + HIW"同意了"+ob->name(1)+HIW"的入队申请。\n"NOR, t,ob);
		message("team", HIW"【组队】"+ob->name(1) + HIW"加入了队伍。\n"NOR, t);
		remove_temp(me);
		remove_temp(ob);
		return 1;
	}
	if( !me->query_temp("pending/team") )
	{
		t = me->query_team();
		message("team", HIW"【组队】"+me->name(1) + HIW"邀请"+ob->name()+HIW"加入队伍。\n"NOR, t);
		tell_object(ob,HIW"【组队】"+me->name()+HIW"邀请你加入队伍。\n"NOR);
		me->set_temp("pending/team",ob);
		tell_object(ob, YEL "如果你愿意加入，请用 team with " + me->parse_command_id_list()[0] + "。\n" NOR);
		return 1;
	}	 
	else if( me->query_temp("pending/team")==ob )
		return notify_fail("你已经向"+ob->name()+"发出了邀请。\n");
	else
	{
		t = me->query_team();
		who = me->query_temp("pending/team");
		if( who )
			tell_object(who,HIW"【组队】"+me->name()+HIW"取消了邀请你加入队伍的意图。\n"NOR);
		message("team", HIW"【组队】"+me->name(1) + HIW"邀请"+ob->name()+HIW"加入队伍。\n"NOR, t);
		tell_object(ob,HIW"【组队】"+me->name()+HIW"邀请你加入队伍。\n"NOR);
		me->set_temp("pending/team",ob);
		tell_object(ob, YEL "如果你愿意加入，请用 team with " + me->parse_command_id_list()[0] + "。\n" NOR);
		return 1;
	}	
}

int help(object me)
{
    write(@HELP
队伍指令使用方法:

team <某人>          - 查看某人的队伍组成。
team with <某人>     - 跟某人组成队伍. 必须要双方都同意加入才会生效。
team dismiss         - 离开队伍. 若下此指令的是领队, 则整个队伍会解散。
team talk <讯息>     - 跟队伍里其他的人谈话, 可以用 tt <讯息> 替代。
team name <队伍名称> - 队长给队伍取一个队名
直接下 team 指令时则会显示你目前是否有加入队伍及队员名单。

注: team 跟 follow 是独立的，你不一定要 follow 队伍的领队。
HELP
    );
    return 1;
}

/*
team form <阵法> - 如果队伍的领队学过阵法的话，可以将队伍中的成员组织成
                   某种阵形，组成阵形的状态只要领队一移动就会解除。
*/                   
