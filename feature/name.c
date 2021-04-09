// name.c

#include <ansi.h>
#include <dbase.h>
#include <condition.h>

nosave string *my_id;
nosave string temp_title;
string title;
string *titles;

string *query_titles(){return titles;}

string query_title(){return title;}

string query_temp_title(){return temp_title;}

mixed set_titles(string arg)
{
	if( !arg || !stringp(arg) )
		return 0;
	if( !titles || sizeof(titles)<1 )
		titles = ({arg});
	else if( member_array(arg,titles)==-1 )
		titles+= ({arg});
	titles-= ({0});
	return titles;		
}

int is_titles(string arg)
{
	if( !titles || !arg || !stringp(arg) )
		return 0;
	arg = COLOR_D->replace_color(arg);	
	if( member_array(arg,titles)==-1 )
		return 0;
	return 1;		
}

mixed set_title(string arg)
{
	string str;
	if( !is_titles(arg) )
	{
		tell_object(this_object(),HIY"【系统】 "HIG+arg+HIY" 为不可设的头衔。\n"NOR);	
		temp_title = 0;
		title = 0;
		return 0;
	}
	if( temp_title && stringp(temp_title) && temp_title!=arg )
	{
		if( str=TITLE_D->unequip_title(this_object(),temp_title) )
		{
			tell_object(this_object(),HIY"【系统】你取消了头衔："+COLOR_D->replace_color(str,1)+HIY" 。\n"NOR);
			if( str=TITLE_D->equip_title(this_object(),arg) )
			{
				tell_object(this_object(),HIY"【系统】你成功将头衔设置为 "+COLOR_D->replace_color(str,1)+HIY" 。\n"NOR);
				temp_title = arg;
				title = arg;
				return arg;
			}
			else
			{
				tell_object(this_object(),HIY"【系统】你设置头衔为 "HIG+arg+HIY" 失败！\n"NOR);
				return 0;
			}
		}
		else	
		{
			tell_object(this_object(),HIY"【系统】你卸除头衔 "HIG+temp_title+HIY" 失败！\n"NOR);
			return 0;
		}
	}
	else if( temp_title && temp_title==arg )
		return arg;
	else
	{
		if( str=TITLE_D->equip_title(this_object(),arg) )
		{
			tell_object(this_object(),HIY"【系统】你成功将头衔设置为 "+COLOR_D->replace_color(str,1)+HIY" 。\n"NOR);
			temp_title = arg;
			title = arg;
			return arg;
		}
		else
		{
			tell_object(this_object(),HIY"【系统】你设置头衔为 "HIG+arg+HIY" 失败！\n"NOR);
			return 0;
		}
	}
}

varargs mixed remove_title(string arg,int raw)
{
	if( !arg || !stringp(arg) )
	{
		TITLE_D->unequip_title(this_object(),temp_title);
		temp_title = 0;
		title = 0;
		titles = 0;
		return 1;		
	}
	
	if( !is_titles(arg) )
		return 0;
	if( temp_title && temp_title==arg )
	{
		TITLE_D->unequip_title(this_object(),temp_title);
		temp_title = 0;
	}
	if( raw )
	{
		titles-= ({arg});	
		title = 0;
	}	
	return 1;
}		

//更新title，上线时
mixed update_title()
{
	if( temp_title )
		return temp_title;
	if( !title )
		return 0;
	return set_title(title);		
}

string *query_my_id()
{
	return my_id;
}

void set_name(string name, string *id)
{
  	set("name", name);
  	set("id", id[0]);
  	my_id = id;
}

int id(string str)
{
  	string *applied_id;

  	if( this_player() && !this_player()->visible(this_object()) ) return 0;

  	if( pointerp(applied_id = query_temp("apply/id")) 
  	 &&  sizeof(applied_id) ) 
   		if( member_array(str, applied_id)!=-1 )
    			return 1;
   		else	return 0;
    
  	if( pointerp(my_id) && member_array(str, my_id)!=-1 )
   		return 1;
  	else	return 0;
}

string *parse_command_id_list()
{
	string *applied_id;

  	if( pointerp(applied_id = query_temp("apply/id")) 
  	 &&  sizeof(applied_id) )
   		return applied_id;
  	else	return my_id;
}

varargs string name(int raw)
{
  	string str, *mask;
  
  	if( !raw && sizeof(mask = query_temp("apply/name")) )
   		return mask[sizeof(mask)-1];
  	else 
  	{
   		if( stringp(str = query("name")) )
    			return str;
   		else	return file_name(this_object());
  	}
}

varargs string short(int raw)
{
	object *team;
  	string t, nick, str, *mask,t_name;
   
  	if( !stringp(str = query("short")) )
   		str = name(raw) + "(" + capitalize(query("id")) + ")";
	if( !this_object()->is_character() ) 
		return str;
	if( !raw && sizeof(mask = query_temp("apply/short")) )
   		str = (string)mask[sizeof(mask)-1];
  	else 
  	{
   		if( stringp(nick = query("nickname")) )
    			str = sprintf("「%s」%s", nick, str);
		if( !raw && sizeof(mask = query_temp("apply/title")) )
            		t = (string)mask[sizeof(mask)-1];
        	else
        	{
        		if( temp_title && stringp(temp_title) )
        		{
        			t = TITLE_D->is_title(temp_title);
        			if( !t || !stringp(t) )
        				t = query("title");
        			else	t = COLOR_D->replace_color(t,1);	
        		}
        		else	t = query("title");
        	}
   		if( t && stringp(t) )
    			str = sprintf("%s %s", t, str);
  	}
	if( !raw ) 
	{
   		if( this_object()->is_ghost() ) 
   			str = HIB "(鬼气) " NOR + str;
		if( pointerp(team = this_object()->query_team()) )
   		{
   			if( stringp(t_name = this_object()->query_team_name()) 
   			 && t_name!="默认组队" )
			{
				t_name = NOR+t_name;
				if( this_object()==this_object()->query_leader() )
					t_name+= "队长 "NOR;
				else	t_name+= "队员 "NOR;	
				str = t_name+str;
			}   			 
   		}	
   		if( query_temp("netdead") ) 
   			str += HIG " <断线中>" NOR;
		if(query_temp("pending/exercising") ) 
			str += HIY " <冥思打坐中> "NOR;
   		if( query_temp("doing_xiudao") ) 
   			str += HIY " <修道中>" NOR;
   		if( in_input() ) 
   			str += HIC " <输入文字中>" NOR;
   		if( in_edit() ) 
   			str += HIY " <编辑档案中>" NOR;
   		if( this_object()->query("PKS")>20 ) 
   			str += HIR " <杀人狂魔>"NOR;
		if( (int)this_object()->is_busy() ) 
			str += YEL " <僵直中>"NOR;		 
		if( this_object()->is_blind() ) 
			str+= HIB" <静默中>"NOR;		 
		if( this_object()->is_hunluan() ) 
			str+= HIR" <混乱中>"NOR;		 
		if( this_object()->is_no_move() ) 
			str+= YEL" <束缚中>"NOR;		 
   		if( interactive(this_object()) &&  query_idle( this_object() ) > 240 )
			str += HIM " <发呆"+chinese_number((query_idle(this_object())-60)/60)+"分钟>" NOR;
		if( this_object()->is_fighting() ) 
			str += HIW " <战斗中>" NOR;
        	if( this_object()->is_yinshen() ) 
        		str += HIC"<隐身中>"NOR;
        	if( !living(this_object()) && query("disable_type") ) 
        		str += HIR + query("disable_type") + NOR;
  		if( this_object()->query("vendor_goods") ) 
  			str += YEL " ㊣" NOR; 
	}
  	return str;
}

varargs string long(int raw)
{
  	string str, extra, *mask;
  
  	if( !raw && sizeof(mask = query_temp("apply/long")) )
   		str = mask[sizeof(mask)-1];
  	else if( !stringp(str = query("long")) )
   		str = short(raw) + "。\n";
	if( stringp(extra = this_object()->extra_long()) )
   		str += extra;
	return str;
}

string level_name(int raw)
{
	string cls,arg,str="";
	int level = this_object()->query_level();
	if( !stringp(cls = this_object()->query("class")) )
		cls = "";
	if( level<10 )
	{
		switch(cls)
		{
			case "yaomo" : return "妖身";
			case "tianmo": return "魔体";
			case "youling" : 
			case "ghost" : return "鬼气";
			default :return "凡人";
		}
	}
	else if( level<40 )
	{
		arg =  "炼气";
		if( level<20 )
			str = "初阶";
		else if( level<30 )
			str = "中阶";
		else	str = "高阶";
		if( raw )
			return arg+str;
		else	return arg+"士";			
	}
	else if( level<50 )
	{
		switch(cls)
		{
			case "yaomo" : arg = "聚灵";break;
			case "tianmo": arg = "聚气";break;
			case "youling" : 
			case "ghost" : arg = "灵动";break;
			case "bonze" : arg = "聚元";break;
			default : arg = "筑基";break;
		}
	}
	else if( level<60 )
	{
		switch(cls)
		{
			case "yaomo" : arg = "通智";break;
			case "tianmo": arg = "炼体";break;
			case "youling" : 
			case "ghost" : arg = "开灵";break;
			case "bonze" : arg = "脱凡";break;
			default : arg = "旋照";break;
		}
	}
	else if( level<70 )
	{
		switch(cls)
		{
			case "yaomo" : arg = "锻体";break;
			case "tianmo": arg = "凝元";break;
			case "youling" : 
			case "ghost" : arg = "魂丹";break;
			case "bonze" : arg = "元心";break;
			default : arg = "融合";break;
		}
	}	
	else if( level<80 )
	{
		switch(cls)
		{
			case "yaomo" : arg = "炼骨";break;
			case "tianmo": arg = "意欲";break;
			case "youling" : 
			case "ghost" : arg = "心炼";break;
			case "bonze" : arg = "意散";break;
			default : arg = "心动";break;
		}
	}
	else if( level<90 )
	{
		switch(cls)
		{
			case "yaomo" : arg = "妖丹";break;
			case "tianmo": arg = "吞噬";break;
			case "youling" : 
			case "ghost" : arg = "灵噬";break;
			case "bonze" : arg = "明心";break;
			default : arg = "金丹";break;
		}
	}
	else if( level<100 )
	{
		switch(cls)
		{
			case "yaomo" : arg = "化形";break;
			case "tianmo": arg = "魔婴";break;
			case "youling" : 
			case "ghost" : arg = "凝体";break;
			case "bonze" : arg = "舍利";break;
			default : arg = "元婴";break;
		}
	}
	else if( level<110 )
	{
		switch(cls)
		{
			case "yaomo" : arg = "凝魄";break;
			case "tianmo": arg = "出窍";break;
			case "youling" : 
			case "ghost" : arg = "凝魄";break;
			case "bonze" : arg = "魂动";break;
			default : arg = "出窍";break;
		}
	}
	else if( level<120 )
	{
		switch(cls)
		{
			case "yaomo" : arg = "神游";break;
			case "tianmo": arg = "离识";break;
			case "youling" : 
			case "ghost" : arg = "炼魂";break;
			case "bonze" : arg = "太虚";break;
			default : arg = "分神";break;
		}
	}
	else if( level<130 )
	{
		switch(cls)
		{
			case "yaomo" : arg = "淬体";break;
			case "tianmo": arg = "合体";break;
			case "youling" : 
			case "ghost" : arg = "归虚";break;
			case "bonze" : arg = "清灵";break;
			default : arg = "合体";break;
		}
	}
	else if( level<140 )
		arg = "渡劫";
	else if( level<150 )
		arg = "大乘";
	else if( level<160 )
	{
		switch(cls)
		{
			case "yaomo" : return "天妖";
			case "tianmo": return "天魔";
			case "bonze" : return "罗汉";
			default : return "灵仙";
		}
	}	
	else if( level<170 )
	{
		switch(cls)
		{
			case "yaomo" : return "玄妖";
			case "tianmo": return "玄魔";
			case "bonze" : return "菩萨";
			default : return "玄仙";
		}
	}	
	else if( level<180 )
	{
		switch(cls)
		{
			case "yaomo" : return "大罗真妖";
			case "tianmo": return "大罗真魔";
			case "bonze" : return "佛陀";
			default : return "大罗金仙";
		}
	}
	else if( level<190 )
		return "准圣";
	else	return "圣人";
	level = last_num(level);
	if( level<4 )
		str = "前期";
	else if( level<6 )	
		str = "中期";
	else	str = "后期";
	if( raw )
		return arg+str;
	else	return arg+"期";
}