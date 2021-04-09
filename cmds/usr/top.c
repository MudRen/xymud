// diablo@xycqII Modified 排除断线玩家进入排行......add busy 位置
#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;
inherit F_DBASE;

string *weapon_type = ({
	"axe","blade","fork","hammer","mace","spear","staff",
	"stick","sword","unarmed","whip",
});	

string *armor_type = ({
    "armor","cloth","hand","kui","neck","pifeng","ring",
    "shield","shoes","waist","wrists",
});	
	
int top_list(object ob1,object ob2);
int top_list2(object ob1,object ob2);
int top_list3(object ob1,object ob2);
int top_list4(object ob1,object ob2);
int top_list5(object ob1,object ob2);
int get_score(object ob);
int get_score2(object ob);
int get_score3(object ob);
int get_score4(object ob);
int get_score5(object ob);

string get_weapon(object weapon)
{
	if( !weapon )
		return "";
      return COLOR_D->clean_color(weapon->name());
}

int have_weapon(object ob,string arg)
{
	object who;
	if( !who=environment(ob) )
		return 0;
    if( !userp(who) || (arg!="weapon" && member_array(arg,weapon_type)==-1 ) )
		return 0;
	if( wizardp(who) ) return 0;
	if( !ob->query("skill_type") )
		return 0;
	if( arg!="weapon" && ob->query("skill_type")!=arg )
		return 0;
	return 1;
}		 	

int have_armor(object ob,string arg)
{
	string type;
	object who;
	if( !who=environment(ob) )
		return 0;
    if( !userp(who) || member_array(arg,armor_type)==-1 ) 
		return 0;
	if( wizardp(who) ) return 0;
	if( !ob->query("armor_type") )
		return 0;
	switch(arg)
	{
		case "armor" : type="armor";break;
		case "cloth" : type="cloth";break;
		case "hand"  : type="hands";break;
		case "kui"   : type="head";break;
		case "neck"  : type="neck";break;
		case "pifeng": type="surcoat";break;
		case "ring"  : type="finger";break;
		case "shield": type="shield";break;
		case "shoes" : type="boots";break;
		case "waist" : type="waist";break;
		case "wrists": type="wrists";break;
		default : return 0;
	}		
		
	if( ob->query("armor_type")!=type )
		return 0;
	return 1;
}

int check_weapon(object me,string arg,int k)
{
	object *list,*ob,weapon;
	int n,i,j;
	string msg,str,str2;

	switch(arg)
	{
		case "axe" 		: str="      鬼      斧      ";break;
		case "blade"	: str="      宝      刀      ";break;
		case "fork"		: str="      神      叉      ";break;
		case "hammer"	: str="      力      锤      ";break;
		case "mace"		: str="      金      锏      ";break;
		case "spear"	: str="      神      枪      ";break;
		case "staff"	: str="      佛      禅      ";break;
		case "stick"	: str="      神      棍      ";break;
		case "sword"	: str="      宝      剑      ";break;
		case "unarmed"	: str="      铁      拳      ";break;
		case "whip"		: str="      神      鞭      ";break;
		case "weapon"	: str="      神      兵      ";break;
		default			: return 0;
	}
	ob = children("/obj/weapon");
	ob = filter_array(ob, "have_weapon" ,this_object(),arg);
	str2 = replace_string(str," ","");
	list = sort_array(ob, (: top_list3 :));
	msg =  "\n              ┏ "HIW"小雨西游"HIC"之"HIR"小雨西游"HIW"在线"+str2+"排行榜"NOR" ┓\n"; 			
	msg += "┏━━━━━┳┻━━━━━━━━┳━━━━━━━━┻━━┳━━┓\n";
	msg += "┃"+BCYN HIW+"  名 次  "NOR+" ┃"+BCYN HIW+"   所   有   者   "NOR+"┃"+BCYN HIW+str+NOR+"┃"+BCYN HIW+"品质"NOR+"┃\n";
	msg += "┣━━━━━╋━━━━━━━━━╋━━━━━━━━━━━╋━━┫\n";
	
	if( k > sizeof(list)) 
		k = sizeof(list);
	for(i = 0 ;i < k ; i++) 
	{ 
		if( !environment(list[i]) )
			continue;
    	if(list[i] == me) msg += BBLU HIY;
		n = get_score3(list[i]);    		
        msg += sprintf(NOR"┃"+HIR+"  %-7s"NOR+" ┃"+HIC+"%-10s"NOR+HIC+"%8s"NOR+"┃"+HIG+"%-22s"NOR+"┃"+HIY+"%4-d"NOR+"┃\n",chinese_number(i+1),environment(list[i])->query("name"),environment(list[i])->query("id"), get_weapon(list[i]),n);
	}
	msg += "┗━━━━━┻━━━━━━━━━┻━━━━━━━━━━━┻━━┛\n";    	
	me->start_more(msg);
	return 1;
}			

int check_armor(object me,string arg,int k)
{
	object *list,*ob,weapon;
	int n,i,j;
	string msg,str,str2;

	switch(arg)
	{
		case "armor"	: str="      宝      甲      ";break;
		case "cloth"	: str="      仙      衣      ";break;
		case "hand"		: str="      神      手      ";break;
		case "kui"		: str="      战      盔      ";break;
		case "neck"		: str="      圣      链      ";break;
		case "pifeng"	: str="      披      风      ";break;
		case "ring"		: str="      仙      戒      ";break;
		case "shield"	: str="      神      盾      ";break;
		case "shoes"	: str="      宝      靴      ";break;
		case "waist"	: str="      金      带      ";break;
		case "wrists"	: str="      仙      镯      ";break;
		default			: return 0;
	}
	ob = children("/obj/armor");
	ob = filter_array(ob, "have_armor" ,this_object(),arg);
	str2 = replace_string(str," ","");
	list = sort_array(ob, (: top_list4 :));
	msg =  "\n              ┏ "HIW"小雨西游"HIC"之"HIR"小雨西游"HIW"在线"+str2+"排行榜"NOR" ┓\n"; 			
	msg += "┏━━━━━┳┻━━━━━━━━┳━━━━━━━━┻━━┳━━━┓\n";
	msg += "┃"+BCYN HIW+"  名 次  "NOR+" ┃"+BCYN HIW+"   所   有   者   "NOR+"┃"+BCYN HIW+str+NOR+"┃"+BCYN HIW+"品  质"NOR+"┃\n";
	msg += "┣━━━━━╋━━━━━━━━━╋━━━━━━━━━━━╋━━━┫\n";
	
	if( k > sizeof(list)) 
		k = sizeof(list);
	for(i = 0 ;i < k ; i++) 
	{ 
		if( !environment(list[i]) )
			continue;
    	if(list[i] == me) msg += BBLU HIY;
		n = get_score4(list[i]);    		
        msg += sprintf(NOR"┃"+HIR+"  %-7s"NOR+" ┃"+HIC+"%-10s"NOR+HIC+"%8s"NOR+"┃"+HIG+"%-22s"NOR+"┃"+HIY+"%6-d"NOR+"┃\n",chinese_number(i+1),environment(list[i])->query("name"),environment(list[i])->query("id"), get_weapon(list[i]),n);
	}
	msg += "┗━━━━━┻━━━━━━━━━┻━━━━━━━━━━━┻━━━┛\n";    	
	me->start_more(msg);
	return 1;
}	

int check_quest(object me,int k)
{
	object *list,*ob;
	int i;
	string msg,arg;	
	if( !me )
		return 0;
	ob = filter_array(users(), (: userp($1) & !wizardp($1)  :));
	list = sort_array(ob, (: top_list5 :));
	msg = "              ┏ "HIC"小雨西游"HIG"在线解谜高手"HIC"排行榜"NOR" ┓\n";
	msg+= "┌───┬──────────┬──────┬──────┐\n";
	msg+= "│"BCYN HIW"名  次"NOR"│"BCYN HIW"      姓   名       "NOR"│"BCYN HIW"   解谜数   "NOR"│"BCYN HIW"获得潜能(万)"NOR"│\n";
	msg+= "├───┼──────────┼──────┼──────┤\n";
	if( k > sizeof(list)) 
		k = sizeof(list);
	for(i = 0 ;i < k ; i++) 
	{ 
    	if(list[i] == me) 
    		msg += BBLU HIY;
		msg+= sprintf("│"NOR HIR"%2d    "NOR"│"HIC"%20-s"NOR"│"HIR"%10-d  "NOR"│"HIR"%10-d  "NOR"│\n",
						(i+1),list[i]->query("name")+"("+capitalize(list[i]->query("id"))+")",
						(int)list[i]->query("quest/number"),
						(list[i]->query("quest/gain/potential")>10000?(list[i]->query("quest/gain/potential")/10000):0),);
	}
	msg+= "└───┴──────────┴──────┴──────┘\n";
	me->start_more(msg);
	return 1;
}	

int main(object me, string arg)
{
	object *list,*ob;
	int n,i,j,k,t=0;
	string msg;
	if( !arg ) 
    	k = 10;
	else    
    {
    	if( sscanf(arg,"%s %d",arg,k)==2 )
        {
        	if( arg!="time" 
        	 && arg!="quests"
        	 && (arg!="weapon" && member_array(arg,weapon_type)==-1 )
        	 && member_array(arg,armor_type)==-1 )
        		return notify_fail("目前只开放 成长速度(time) 与 神兵(weapon|axe|blade|fork|hammer|mace|spear|staff|stick|sword|unarmed|whip) 以及
神器(armor|cloth|hand|kui|neck|pifeng|ring|shield|shoes|waist|wrists)的即时排行。\n");
			if( arg=="time" )        		
				t = 1;
			else if( arg=="quests" )
				t = 4;
			else if( arg=="weapon" || member_array(arg,weapon_type)!=-1 )
				t = 2;	
			else if( member_array(arg,armor_type)!=-1 )
				t = 3;	
		}
        else if( sscanf(arg,"%d",k)!=1 )
        	k = 10;
	}				 

    if( k < 10) k = 10;
    if( k > 50) k = 50;

	if(me->query("sen")<80 ) 
		return notify_fail("你太累了,歇歇吧.\n");                                                                                                            
	if( query_temp("last_top_time") && !wizardp(me) && (query_temp("last_top_time")+60)>time() )                                                                            
    	return notify_fail("等等,系统喘气中......\n");                    
	me->add("sen",-10);                                                                                                                                                           
	set_temp("last_top_time",time());        
	
	if( t==2 )
		return check_weapon(me,arg,k);
	else if( t==3 )
	    return check_armor(me,arg,k);
	else if( t==4 )
		return check_quest(me,k);
	ob = filter_array(users(), (: userp($1) & !wizardp($1)  :));
	if( t<1 )
	{
		list = sort_array(ob, (: top_list :));
		msg =  "\n              ┏ "HIW"小雨西游"HIC"之"HIR"小雨西游"HIW"在线高手排行榜"NOR" ┓\n"; 
		msg += "┏━━━━━┳┻━━━━━━━━━━━┳━━━━━┻┳━━━━┓\n";
		msg += "┃"+BCYN HIW+"  名 次  "NOR+" ┃"+BCYN HIW+"      高        手      "NOR+"┃"+BCYN HIW+"  门    派  "NOR+"┃"+BCYN HIW+" 评  价 "NOR+"┃\n";
		msg += "┣━━━━━╋━━━━━━━━━━━━╋━━━━━━╋━━━━┫\n";	
	}
	else
	{
		list = sort_array(ob, (: top_list2 :));	
		msg =  "\n              ┏ "HIW"小雨西游"HIC"之"HIR"小雨西游"HIW"在线快手排行榜"NOR" ┓\n"; 	
		msg += "┏━━━━━┳┻━━━━━━━━━━━┳━━━━━┻┳━━━━┓\n";
		msg += "┃"+BCYN HIW+"  名 次  "NOR+" ┃"+BCYN HIW+"      快        手      "NOR+"┃"+BCYN HIW+"  门    派  "NOR+"┃"+BCYN HIW+"速度(分)"NOR+"┃\n";
		msg += "┣━━━━━╋━━━━━━━━━━━━╋━━━━━━╋━━━━┫\n";
	}
	if( k > sizeof(list)) 
		k = sizeof(list);

	for(i = 0 ;i < k ; i++) 
	{ 
		if( !environment(list[i]) )
			continue;
    	if(list[i] == me) msg += BBLU HIY;
		if( t<1 )
       		n = get_score(list[i]);
		else
       		n = get_score2(list[i]);	
		msg += sprintf(NOR"┃"+HIR+"  %-7s"NOR+" ┃"+HIC+" %-12s"NOR+HIC+" %-10s"NOR+"┃"+HIG+"%-12s"NOR+"┃"+HIY+" %5d"NOR+"  ┃\n",chinese_number(i+1),list[i]->query("name"),"["+ list[i]->query("id")+"]", list[i]->query("family")? list[i]->query("family/family_name"):"普通百姓",n);
	}
	msg += "┗━━━━━┻━━━━━━━━━━━━┻━━━━━━┻━━━━┛\n";    
	if( t<1 )
		msg +=  "\n "+HIW+"你目前的评价是："+get_score(me)+"\n";
	else
		msg +=  "\n "+HIW+"你目前的成长速度是："+get_score2(me)+"\n";		 	                         
	me->start_more(msg);
	return 1;
}
                                                                                      
int top_list(object ob1, object ob2)
{
	int score1,score2;
	reset_eval_cost();
	score1 = get_score(ob1);
	score2 = get_score(ob2);
	return score2 - score1;
}

int get_score(object ob)
{
	int tlvl,i,score;
	string *ski;
	mapping skills;
	int exp; 

	reset_eval_cost();
	exp = ob->query_level()*10;
	if( exp<1 )
		exp = 1;
	skills = ob->query_skills();
	if( !skills || !mapp(skills) )
                return exp/10+1;
	ski  = keys(skills);
	if( !ski || !arrayp(ski) || sizeof(ski)<1 )
                return exp/10+1;
	tlvl = 0;	
	for(i = 0; i<sizeof(ski); i++) 
    		tlvl += skills[ski[i]];
	tlvl/= sizeof(ski);
	score = exp+tlvl; 
	score += ob->query_maxforce()/50;
	score += ob->query_maxmana()/50;
	score += ob->query_maxkee()/50;
	score += ob->query_maxsen()/50;
	score += (ob->query_str() + ob->query_int() + ob->query_spi() + ob->query_con())/40; 
	score/= 10;
	if( score<1 )
		score = 1;
	return score;
}

int top_list2(object ob1, object ob2)
{
	int score1,score2;
	reset_eval_cost();
	score1 = get_score2(ob1);
	score2 = get_score2(ob2);
	return score2 - score1;
}

int get_score2(object ob)
{
	int tt,t,t2;
	if( !ob )
		return 0;
		
	tt = ob->query_temp("login_data/time");
	tt = time()-tt;
 	tt/= 60;
 	if( tt<1 ) tt = 1;
 	
        t = ob->query("combat_exp")-ob->query_temp("last_login/exp");
	t = t/tt;
	if( t<0 ) t = 0;

	t2 = ob->query("daoxing")-ob->query_temp("last_login/dx");
	t2 = t2/tt;
	if( t2<0 ) t2 = 0;
	t = t+t2;
	t/= 2;
	return t;
}

int top_list3(object ob1, object ob2)
{
	int score1,score2;
	reset_eval_cost();
	score1 = get_score3(ob1);
	score2 = get_score3(ob2);
	return score2 - score1;
}

int top_list4(object ob1, object ob2)
{
	int score1,score2;
	reset_eval_cost();
	score1 = get_score4(ob1);
	score2 = get_score4(ob2);
	return score2 - score1;
}

int get_score5(object ob)
{
	int tt,t,t2;
	if( !ob )
		return 0;
	if( ob->query("quest")==0 )
		return 0;
	return ob->query("quest/number");
}

int top_list5(object ob1, object ob2)
{
	int score1,score2;
	reset_eval_cost();
	score1 = get_score5(ob1);
	score2 = get_score5(ob2);
	return score2 - score1;
}

int get_score3(object ob)
{
	int v,i;
	mapping tmp;
	object weapon;
	string *prop;
	
	if( !ob )
		return 0;
	weapon = ob;		
	v = (weapon->query("weapon_prop/combat_damage")+weapon->query("weapon_prop/spells_damage"))/20;
	tmp = weapon->query("weapon_prop");
	prop = keys(tmp);
	for(i=0;i<sizeof(prop);i++)
	{
		if( prop[i]=="combat_damage" 
		 || prop[i]=="spells_damage" ) 
			continue;
		v+= 1;
	}
	return v;		
}

int get_score4(object ob)
{
	int v,i;
	object weapon;
	mapping tmp;
	string *prop;
	
	if( !ob )
		return 0;
	weapon = ob;		
	v = (weapon->query("armor_prop/combat_def")+weapon->query("armor_prop/spells_def"))/20;
	tmp = weapon->query("armor_prop");
	prop = keys(tmp);
	for(i=0;i<sizeof(prop);i++)
	{
		if( prop[i]=="combat_def"
		 || prop[i]=="spells_def"
		 || prop[i]=="armor" )
			continue;
		v+= 1;	
	}
	return v;		
}

int help(object me)
{
write(@HELP
指令格式 : top  [数字]
 
这个指令可以让你知道在线高手是哪些，别去惹他们。
 
 	   top time [数字]
这个指令可以让你知道在线最有潜质的是哪些，看好他们哦。
 
           top <axe|blade|fork|hammer|mace|spear|staff|stick|sword|unarmed|whip> [数字]
这个指令可以让你知道在线最好的指定类武器是哪些，加油哦。

           top weapon [数字]
这个指令可以让你知道在线最好的召唤类武器是哪些，加油哦。

HELP
    );
    return 1;
}

