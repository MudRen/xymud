// cracked by vikee 2/09/2002   vikee@263.net
// team.c
#include <ansi.h>
#include <command.h>
#include <dbase.h>
#include <origin.h>

nosave object leader, *team;
nosave string leader_id;
nosave object follow;
nosave string team_name;

string friend; //friend = snowtu#2^snowi#1^

//好感度
int friend_pot(object who)
{
	string *dir,id,temp;
	int i,d;
	if( !who || !userp(who) || !who->query("id") )
		return 0;
	if( !friend && strlen(friend)<1 )
		return 0;	
	if( strsrch(friend,who->query("id"))==-1 )
		return 0;
	dir = explode(friend,"^");
	if( !dir || !arrayp(dir) )
		return 0;
	i = sizeof(dir);
	while(i--)
	{
		temp = dir[i];
		if( temp || sscanf(temp,"%s#%d",id,d)==2 )
		{
			if( id==who->query("id") )
				return d;
			else	continue;	
		}
		else	continue;	
	}
	return 0;
}

int add_friend(object who,int p)
{
	string id,temp,*dir,ff,oid;
	int i,old;
	if( !who || !userp(who) || p==0 )
		return 0;
	id = who->query("id");
	if( !id )
		return 0;	
	temp = id+"#"+p;
	if( !friend )
		friend = temp+"^";
	dir = explode(friend,"^");
	if( !dir || !arrayp(dir) )
		friend = temp+"^";
	else
	{
		i = sizeof(dir);
		ff = "";
		while(i--)
		{
			if( !dir[i] || sscanf(dir[i],"%s#%d",oid,old)!=2 )
				continue;
			if( oid!=id )
				ff+= dir[i]+"^";
			else
			{
				p = old+p;
				if( p==0 )
					continue;
				ff+= id+"#"+p+"^";	
			}		
		}
		friend = ff;
	}
	return p;
}

int team_buff()
{
	int i,p;
	if( !team || !arrayp(team) )
		return 0;
	if( sizeof(team)<3 )
		return 0;
	p = 0;
	i = sizeof(team);
	while(i--)
	{
		p+= friend_pot(team[i]);	
	}
	p = p/i;
	if( p<1 )
		return 0;
	if( p>150 )
		p = 150;
	return p;	
}

int set_leader(object ob)
{
	if( leader )
		return 0;
	if( !ob )
		ob = this_object();	
	leader = ob;
	leader_id = ob->query("id");
	return 1;
}

object query_leader() { return leader; }

string query_team_name()
{
	if( !team_name || !stringp(team_name) )
		return "默认组队";
	return team_name;
}

void set_team_name(string v)
{
	if( team_name && stringp(team_name) )
		return;
	team_name = v;
}		

int set_follow(object ob)
{
	object me = this_object();
	if( !ob )
	{
		if( follow )
		{
			if(follow->visible(me)) 
				tell_object(follow,HIW+me->name()+HIW"取消了跟随你的动作。"NOR"\n");
			tell_object(me,HIW"你取消了跟随"+follow->name()+HIW"的动作。"NOR"\n");				
		}
		follow = 0;
		return 1;
	}	
	if( ob==this_object() )
		return 0;
	if( follow )
	{
		if( follow!=ob )
		{
			if(follow->visible(me))
				tell_object(follow,HIW+me->name()+HIW"取消了跟随你的动作。"NOR"\n");
			tell_object(me,HIW"你取消了跟随"+follow->name()+HIW"的动作。"NOR"\n");					
			follow = ob;
			if(ob->visible(me))
				tell_object(ob,HIW+me->name()+HIW"决定开始跟随你一起行动。\n"NOR);
			tell_object(me,HIW"你决定跟随"+follow->name()+HIW"一起行动。"NOR"\n");
			return 1;
		}
		else
		{
			tell_object(me,HIW"你已经在跟随"+follow->name()+HIW"了。"NOR"\n");	
			return 0;
		}	
	}
	if( ob->query_follow()==me )
	{
		tell_object(me,HIW+ob->name()+HIW"已经跟随你一起行动了。"NOR"\n");
		return 0;
	}
	if(me->visible(ob))
	{
		follow = ob;
		if(ob->visible(me))
			tell_object(ob,HIW+me->name()+HIW"决定开始跟随你一起行动。"NOR"\n");
		tell_object(me,HIW"你决定跟随"+follow->name()+HIW"一起行动。"NOR"\n");
		return 1;
	}
	else	return 0;
}		

object query_follow() { return follow; }

int follow_path(string dir)
{
	if( (origin()==ORIGIN_LOCAL) || (origin()==ORIGIN_CALL_OUT) ) 
	{
		this_object()->remove_all_enemy();
		reset_eval_cost();
		return GO_CMD->main(this_object(), dir);
	}
}

int follow_me(object ob, string dir)
{
	if( !ob || !living(this_object()) || ob==this_object() ) 
		return 0;
	if( ob==follow
	||(query("pursuer") && this_object()->is_killing(ob->query("id")))) 
	{
		if( random(ob->query_cor())>this_object()->query("cor")/5 )
		{
			remove_call_out("follow_path");
			call_out("follow_path",0, dir);
			return 1;
		}
		return follow_path(dir);
	}
	return 0;
}

int add_team_member(object ob)
{
	if( ob==this_object() ) return 0;

	if( arrayp(team) ) {
		if( member_array(ob, team)==-1 ) {
			team += ({ ob });
			for(int i=sizeof(team)-1; i>=0; i--)
				team[i]->set_team(team);
		} else
			return 0;
	} else {
		team = ({ this_object(), ob });
		ob->set_team(team);
	}
	return 1;
}

varargs int is_team_leader(object who)
{
	if( !leader )
		return 0;
	if( !who )
		who = this_player();
	return 	who==leader;
}

int set_team(object *t)
{
	team = t;
}

void remove_team()
{
	team = 0;
	leader = 0;
	leader_id = 0;
	team_name = 0;
}

varargs int dismiss_team(object ob)
{
	int i;

	if( !arrayp(team) ) return 0;
	
	team-= ({0});
	
	if( !ob ) 
	{
		if( this_object()==leader ) 
		{
			for(i=1; i<sizeof(team); i++)
				team[i]->remove_team();
		} else 
		{
			for(i=0; i<sizeof(team); i++)
				team[i]->dismiss_team( this_object() );
		}
		remove_team();
	} 
	else	
	{
		team -= ({ ob });
		ob->remove_team();
		if( team && sizeof(team)<2 )
		{
			message("team",HIW"【组队】由于队员不足2人，队伍自动解散。"NOR"\n",team);
			remove_team();
		}
	}
	return 1;
}

object *query_team()
{
	return team;
}

