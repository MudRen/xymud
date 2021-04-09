// look.c
//neva 为 xserver双头龙模式改写 2003年2月7日

#include <room.h>
#include <ansi.h>
#include <color.h>
#include <combat.h>
inherit F_CLEAN_UP;


int webmain(object me, string arg);//用网页玩的
int weblook_room(object me, object env);//用网页玩的
int weblook_item(object me, object obj);//用网页玩的
int weblook_living(object me, object obj, string arg);//用网页玩的
int weblook_room_item(object me, string arg);//用网页玩的



int mudmain(object me, string arg);//用ZMUD连入的
int mudlook_room(object me, object env);//用ZMUD连入的
int mudlook_item(object me, object obj);//用ZMUD连入的
int mudlook_living(object me, object obj);//用ZMUD连入的
int mudlook_room_item(object me, string arg);//用ZMUD连入的
string getper(object me, object obj);//共用的
string tough_level(int power);//共用的
string gettof(object me, object obj);//共用的
string getdam(object me, object obj);//共用的

string *tough_level_desc = ({
        BLU "不堪一击" NOR,BLU "毫不足虑" NOR,BLU "不足挂齿" NOR,BLU "初学乍练" NOR,BLU "勉勉强强" NOR,
        HIB "初窥门径" NOR,HIB "初出茅庐" NOR,HIB "略知一二" NOR,HIB "普普通通" NOR,HIB "平平淡淡" NOR,
        CYN "平淡无奇" NOR,CYN "粗通皮毛" NOR,CYN "半生不熟" NOR,CYN "马马虎虎" NOR,CYN "略有小成" NOR,
        HIC "已有小成" NOR,HIC "鹤立鸡群" NOR,HIC "驾轻就熟" NOR,HIC "青出于蓝" NOR,HIC "融会贯通" NOR,
        GRN "心领神会" NOR,GRN "炉火纯青" NOR,GRN "了然于胸" NOR,GRN "略有大成" NOR,GRN "已有大成" NOR,
        YEL "豁然贯通" NOR,YEL "出类拔萃" NOR,YEL "无可匹敌" NOR,YEL "技冠群雄" NOR,YEL "神乎其技" NOR,
        HIY "出神入化" NOR,HIY "非同凡响" NOR,HIY "傲视群雄" NOR,HIY "登峰造极" NOR,HIY "无与伦比" NOR,
        HIM "所向披靡" NOR,HIM "一代宗师" NOR,HIM "精深奥妙" NOR,HIM "神功盖世" NOR,HIM "举世无双" NOR,
        HIR "惊世骇俗" NOR,HIR "撼天动地" NOR,HIR "震古铄今" NOR,HIR "超凡入圣" NOR,HIR "威镇寰宇" NOR,
        RED "空前绝后" NOR,RED "天人合一" NOR,MAG "深藏不露" NOR,WHT "深不可测" NOR,HIW "返璞归真" NOR
});
string *heavy_level_desc= ({
	"极轻",
	"很轻",
	"不重",
	"不知轻重",
	"不轻",
	"很重",
	"极重",
	"举重若轻",
	"举轻若重",
	"……呀！你竟然看不出。。"
});
void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob = this_player();     	
	int result;


if( ob->query("position") == "zmuduser" ) 
result = mudmain(me, arg);//如果身上有这个记号就调用MUDMAIN
	else 
result = webmain(me, arg);//如果身上没有记号就调用WEBMAIN
	return result;
}
//******************************************************
//如果是用网页玩的执行这一部份的LOOK
int webmain(object me, string arg)
{
	object obj;        
	int result;

	if( !arg ) result = weblook_room(me, environment(me));
	else if( (obj = present(arg, me)) || (obj = present(arg, environment(me)))) {
		if( obj->is_character() ) result = weblook_living(me, obj, arg);
		else result = weblook_item(me, obj);
	} else result = weblook_room_item(me, arg);

	return result;
}

int weblook_room(object me, object env)
{
	int i;
	object *inv;
	mapping exits;
	string str, desc, *dirs;
	mapping buffo = ([]), buffobj = ([]);
	string bfile;//file_name,name;
	string short, long, exit;

	if( !env ) {
		write("你的四周灰蒙蒙地一片，什么也没有。\n");
		return 1;
	}
	short = sprintf(WEBBLK "【" WEBNOR WEBRED " %s"  WEBNOR WEBBLK "】" + WEBNOR, env->query("short"));
	short += wizardp(me)? file_name(env): "";

//	short += wizardp(me)? file_name(env)+sprintf(" - (%d,%d,%d)",env->query("coor/x"),
//		env->query("coor/y"),env->query("coor/z")): "";
	desc = env->query("long");
//	long = implode(explode(desc, "\n"), "");

        long = desc + "<br>　　" + WEBYEL +
	        implode(explode((env->query("outdoors")?"":"窗外：") + NATURE_D->outdoor_room_description(), "\n"), "")  + WEBNOR;

	exit = "";
  	if( mapp(exits = env->query("exits")) )
  	{
                  dirs = keys(exits);
                  for(i=0; i<sizeof(dirs); i++)
                          if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
                                dirs[i] = 0;
                  dirs -= ({ 0 });
                  if( sizeof(dirs)==0 )
                          exit = "    这里没有任何明显的出路。";
                  else if( sizeof(dirs)==1)
                          exit = "    这里唯一的出口是 <a target=nothing href=\\\"/Command/go "  + dirs[0] + "\\\"" + WEBRED + dirs[0]  + "</a>" + WEBNOR + "。";
                  else
                  {
                   exit = "    这里明显的出口是 ";
                   for (i = 0; i < sizeof(dirs) - 2; i++)
                  		 exit += sprintf("<a target=nothing href=\\\"/Command/go %s\\\">%s</a>、", dirs[i], dirs[i]);
          		exit += sprintf("<a target=nothing href=\\\"/Command/go %s\\\">%s</a>和", dirs[sizeof(dirs) - 2], dirs[sizeof(dirs) - 2]);
          		exit += sprintf("<a target=nothing href=\\\"/Command/go %s\\\">%s</a>", dirs[sizeof(dirs) - 1], dirs[sizeof(dirs) - 1]);
                }                            
        }


	inv = all_inventory(env);
	str = "";
	for(i=0; i<sizeof(inv); i++) {
		if( inv[i]==me ) continue;
		if( inv[i]->query("no_shown")) continue;
		if( !me->visible(inv[i]) ) continue;
//		str += "  " + inv[i]->short() + "<br>";
                bfile=base_name(inv[i]);
                if ( member_array(bfile,keys(buffo)) == -1 )
                {
                       buffo[bfile]=1;
                       buffobj[bfile]=inv[i];
                       //str += sprintf("<a target=nothing href=\\\"/Command/look %s\\\"><img border=0 src=/image/%s.gif>%s</a><br>",
                         //      	inv[i]->query("id"), inv[i]->query("img"), inv[i]->short());
                               	str += sprintf("<a target=nothing href=\\\"/Command/look %s\\\">%s</a><br><br>",
                               	inv[i]->query("id"), inv[i]->short());
                }
                else 
                {
                        buffo[bfile] ++;
            //            str += sprintf("<a target=nothing href=\\\"/Command/look %s %d\\\"><img border=0 src=/image/%s.gif>%s</a><br>",
            //            inv[i]->query("id"), buffo[bfile], inv[i]->query("img"), inv[i]->short());
                         str += sprintf("<a target=nothing href=\\\"/Command/look %s %d\\\">%s</a><br><br>",
                        inv[i]->query("id"), buffo[bfile], inv[i]->short());
               }
	}


        printf(JSP "parent.show_inv(\"%s\")" NSP, str);
        printf(JSP "parent.look_room(\"%s\", \"%s\", \"%s\")" NSP, short, long, exit);

//        printf(JSP "parent.show_inv(\"%s\")" NSP, str);
//        printf(JSP "parent.look_room(\"%s\", \"%s\", \"%s\")" NSP, short, long, exit);
	
	return 1;
}
int weblook_item(object me, object obj)
{
	mixed *inv;
	string prep;

	write(obj->long());
	inv = all_inventory(obj);
	if( !obj->is_closed() && sizeof(inv)) {
		switch( (string)obj->query("prep") ) {
			case "on":
				prep = "上";
				break;
			case "under":
				prep = "下";
				break;
			case "behind":
				prep = "后";
				break;
			case "inside":
				prep = "里";
				break;
			default:
				prep = "里";
				break;
                        }
		inv = map_array(inv, "inventory_look", this_object() );
		message("vision", sprintf("%s面有：\n  %s\n", prep,
			implode(inv, "\n  ") ), me);
	}
	return 1;
}

int weblook_living(object me, object obj, string arg)
{
	string str, limb_status, pro;
	mixed *inv;
	mapping my_fam, fam;

	if( me!=obj )
		message("vision", me->name() + "正盯著你看，不知道打些什么主意。\n", obj);

	str = obj->long();
	pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));

	if( (string)obj->query("race")=="人类"
	&&	intp(obj->query("age")) )
		if(userp(obj))
		str +=  sprintf("%s看起来象%s多岁。\n", pro, chinese_number(obj->query("age") / 10 * 10),
				obj->query("national"));
		else
		str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(obj->query("age") / 10 * 10));
		str+=getper(me,obj);
		str +=sprintf("武功看起来好象");
		str+=gettof(me,obj);
		str += sprintf("，");
		str +=sprintf("出手似乎");
		str +=getdam(me,obj);
                str += sprintf("。\n");
	// If we both has family, check if we have any relations.
	if( obj!=me
	&&	mapp(fam = obj->query("family"))
	&&	mapp(my_fam = me->query("family")) 
	&&	fam["family_name"] == my_fam["family_name"] ) {
	
		if( fam["generation"]==my_fam["generation"] ) {
			if( (string)obj->query("gender") == "男性" )
				str += sprintf( pro + "是你的%s%s。\n",
					my_fam["master_id"] == fam["master_id"] ? "": "同门",
					my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
			else
				str += sprintf( pro + "是你的%s%s。\n",
					my_fam["master_id"] == fam["master_id"] ? "": "同门",
					my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
		} else if( fam["generation"] < my_fam["generation"] ) {
			if( my_fam["master_id"] == obj->query("id") )
				str += pro + "是你的师父。\n";
			else if( my_fam["generation"] - fam["generation"] > 1 )
				str += pro + "是你的同门长辈。\n";
			else if( fam["enter_time"] < my_fam["enter_time"] )
				str += pro + "是你的师伯。\n";
			else
				str += pro + "是你的师叔。\n";
		} else {
			if( fam["generation"] - my_fam["generation"] > 1 )
				str += pro + "是你的同门晚辈。\n";
			else if( fam["master_id"] == me->query("id") )
				str += pro + "是你的弟子。\n";
			else
				str += pro + "是你的师侄。\n";
		}
	}

	if( obj->query("max_kee") )
		str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_kee") * 100 / (int)obj->query("max_kee")) + "\n";

	inv = all_inventory(obj);
	if( sizeof(inv) ) {
		inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
		inv -= ({ 0 });
		if( sizeof(inv) )
			str += sprintf( obj->is_corpse() ? "%s的遗物有：\n%s\n" : "%s身上带著：\n%s\n",
				pro, implode(inv, "\n") );
	}

	message("vision", str, me);
	printf(JSP "parent.look_living(\"%s\", \"%s\")" NSP, str, arg);

	if( obj!=me 
	&&	living(obj)
	&&	random((int)obj->query("bellicosity")/10) > (int)me->query_per() ) {
		write( obj->name() + "突然转过头来瞪你一眼。\n");
		COMBAT_D->auto_fight(obj, me, "berserk");
	}

	return 1;
}

int weblook_room_item(object me, string arg)
{
	object env;
	mapping item, exits;

	if( !objectp(env = environment(me)) )
		return notify_fail("这里只有灰蒙蒙地一片，什么也没有。\n");

	if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) {
		if( stringp(item[arg]) )
			write(item[arg]);
		else if( functionp(item[arg]) )
			write((string)(*item[arg])(me));
			
		return 1;
	}
	if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
		if( objectp(env = find_object(exits[arg])) )
			weblook_room(me, env);
		else {
			call_other(exits[arg], "???");
			weblook_room(me, find_object(exits[arg]));
		}
		return 1;
	}
	return notify_fail("你要看什么？\n");
}
//******************************************************







//######################################################
//如果是用ZMUD玩的执行这一部份的LOOK
int mudmain(object me, string arg)
{
	object obj;        
	int result;

	if( !arg ) result = mudlook_room(me, environment(me));
	else if( (obj = present(arg, me)) || (obj = present(arg, environment(me)))) {
		if( obj->is_character() ) result = mudlook_living(me, obj);
		else result = mudlook_item(me, obj);
	} else result = mudlook_room_item(me, arg);

	return result;
}

int mudlook_room(object me, object env)
{
	int i;
	object *inv;
	mapping exits;
	string str, *dirs;

	if( !env ) {
		write("你的四周灰蒙蒙地一片，什么也没有。\n");
		return 1;
	}
	str = sprintf(   WHT + "【%s"+WHT+"】" + NOR + " - %s\n    %s%s",

env->query("short"),
		wizardp(me)? file_name(env): "",
		env->query("long"),
		env->query("outdoors")? NATURE_D->outdoor_room_description() : "" );

	if( mapp(exits = env->query("exits")) ) {
		dirs = keys(exits);
		for(i=0; i<sizeof(dirs); i++)
			if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
				dirs[i] = 0;
		dirs -= ({ 0 });
		if( sizeof(dirs)==0 )
			str += "    这里没有任何明显的出路。\n";
		else if( sizeof(dirs)==1 )
			str += "    这里唯一的出口是 " + WHT + dirs[0] + NOR + "。\n";
		else
			str += sprintf("    这里明显的出口是 " + WHT + "%s" + NOR + " 和 " + WHT + "%s" + NOR + "。\n",
				implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
	}
	else str += "    这里没有任何明显的出路。\n";

//	str += env->door_description();

	inv = all_inventory(env);
	for(i=0; i<sizeof(inv); i++) {
		if( inv[i]==me ) continue;
		if( inv[i]->query("no_shown")) continue;
		if( !me->visible(inv[i]) ) continue;
		str += "  " + inv[i]->short() + "\n";
	}

	write(str);
	return 1;
}

int mudlook_item(object me, object obj)
{
	mixed *inv;
	string prep;

	write(obj->long());
	inv = all_inventory(obj);
	if( !obj->is_closed() && sizeof(inv)) {
		switch( (string)obj->query("prep") ) {
			case "on":
				prep = "上";
				break;
			case "under":
				prep = "下";
				break;
			case "behind":
				prep = "后";
				break;
			case "inside":
				prep = "里";
				break;
			default:
				prep = "里";
				break;
                        }
		inv = map_array(inv, "inventory_look", this_object() );
		message("vision", sprintf("%s面有：\n  %s\n", prep,
			implode(inv, "\n  ") ), me);
	}
	return 1;
}
int mudlook_living(object me, object obj)
{
	string str, limb_status, pro;
	mixed *inv;
	mapping my_fam, fam;

	if( me!=obj )
		message("vision", me->name() + "正盯著你看，不知道打些什么主意。\n", obj);

	str = obj->long();
	pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));

	if( (string)obj->query("race")=="人类"
	&&	intp(obj->query("age")) )
		if(userp(obj))
		str +=  sprintf("%s看起来象%s多岁。\n", pro, chinese_number(obj->query("age") / 10 * 10),
				obj->query("national"));
		else
		str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(obj->query("age") / 10 * 10));
		str+=getper(me,obj);
		str +=sprintf("武功看起来好象");
		str+=gettof(me,obj);
		str += sprintf("，");
		str +=sprintf("出手似乎");
		str +=getdam(me,obj);
                str += sprintf("。\n");
	// If we both has family, check if we have any relations.
	if( obj!=me
	&&	mapp(fam = obj->query("family"))
	&&	mapp(my_fam = me->query("family")) 
	&&	fam["family_name"] == my_fam["family_name"] ) {
	
		if( fam["generation"]==my_fam["generation"] ) {
			if( (string)obj->query("gender") == "男性" )
				str += sprintf( pro + "是你的%s%s。\n",
					my_fam["master_id"] == fam["master_id"] ? "": "同门",
					my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
			else
				str += sprintf( pro + "是你的%s%s。\n",
					my_fam["master_id"] == fam["master_id"] ? "": "同门",
					my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
		} else if( fam["generation"] < my_fam["generation"] ) {
			if( my_fam["master_id"] == obj->query("id") )
				str += pro + "是你的师父。\n";
			else if( my_fam["generation"] - fam["generation"] > 1 )
				str += pro + "是你的同门长辈。\n";
			else if( fam["enter_time"] < my_fam["enter_time"] )
				str += pro + "是你的师伯。\n";
			else
				str += pro + "是你的师叔。\n";
		} else {
			if( fam["generation"] - my_fam["generation"] > 1 )
				str += pro + "是你的同门晚辈。\n";
			else if( fam["master_id"] == me->query("id") )
				str += pro + "是你的弟子。\n";
			else
				str += pro + "是你的师侄。\n";
		}
	}

	if( obj->query("max_kee") )
		str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_kee") * 100 / (int)obj->query("max_kee")) + "\n";

	inv = all_inventory(obj);
	if( sizeof(inv) ) {
		inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
		inv -= ({ 0 });
		if( sizeof(inv) )
			str += sprintf( obj->is_corpse() ? "%s的遗物有：\n%s\n" : "%s身上带著：\n%s\n",
				pro, implode(inv, "\n") );
	}

	message("vision", str, me);

	if( obj!=me 
	&&	living(obj)
	&&	random((int)obj->query("bellicosity")/10) > (int)me->query_per() ) {
		write( obj->name() + "突然转过头来瞪你一眼。\n");
		COMBAT_D->auto_fight(obj, me, "berserk");
	}

	return 1;
}

int mudlook_room_item(object me, string arg)
{
	object env;
	mapping item, exits;

	if( !objectp(env = environment(me)) )
		return notify_fail("这里只有灰蒙蒙地一片，什么也没有。\n");

	if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) {
		if( stringp(item[arg]) )
			write(item[arg]);
		else if( functionp(item[arg]) )
			write((string)(*item[arg])(me));
			
		return 1;
	}
	if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
		if( objectp(env = find_object(exits[arg])) )
			mudlook_room(me, env);
		else {
			call_other(exits[arg], "???");
			mudlook_room(me, find_object(exits[arg]));
		}
		return 1;
	}
	return notify_fail("你要看什么？\n");
}
//######################################################















string getper(object me, object obj)
{
	int per;
	int spi;

	int weight;
	string str;

	per = obj->query_per();
	spi = me->query_spi();
       
// 灵性差的人看的不准
	if (spi>35) weight = 0;
	else weight = (int)(35 - spi)/4 ;


	if (random(10)>6) per = per - weight;
	else per = per + weight ;

	
	if ((string) obj->query("gender") == "男性") {
		 if (per >= 30) str = HIW"长得宛如玉树临风，风流倜傥，顾盼之间，神采飞扬。真正是人中龙凤！\n"NOR;
                if ((per >= 26) && (per < 30))
                        str = HIC"英俊潇洒，气宇轩昂，风度翩翩，面目俊朗，貌似潘安。\n"NOR;
                if ((per >= 22) && (per < 26))
                        str = HIG"相貌英俊，仪表堂堂。骨格清奇，丰姿非俗。\n"NOR;
                if ((per >= 18) && (per < 22))
                        str = HIY"五官端正。\n"NOR;
                if ((per >= 15) && (per < 18))
                        str = HIB"相貌平平。没什么好看的。\n"NOR;
                if (per < 15)
                        str = RED"长得...有点对不住别人。\n"NOR;
	}
	else if  ((string) obj->query("gender") == "女性"){
		if (per >= 30)
                        str = HIW"有倾国倾城之貌，容色丽都，娇艳绝伦，堪称人间仙子！\n长发如云，肌肤胜雪，风华绝代，不知倾倒了多少英雄豪杰。\n"NOR;
                if ((per >= 28) && (per < 30))
                        str = HIC"清丽绝俗，风姿动人。有沉鱼落雁之容，避月羞花之貌！\n俏脸生春，妙目含情，顾盼神飞，轻轻一笑，不觉让人怦然心动。\n"NOR;
                if ((per >= 26) && (per < 28))
                        str = HIG"肤如凝脂，眉目如画，风情万种，楚楚动人。当真是我见犹怜！\n"NOR;
                if ((per >= 24) && (per < 26))
                        str = HIM"容色秀丽，面带晕红，眼含秋波。举手投足之间，确有一番风韵。\n"NOR;
                if ((per >= 21) && (per < 24))
                        str = HIR"气质高雅，面目姣好，虽算不上绝世佳人，也颇有几份姿色。\n"NOR;
                if ((per >= 18) && (per < 21))
                        str = HIY"相貌平平，还看得过去。\n"NOR;
                if ((per >= 15) && (per <18))
                        str = HIB"的相貌嘛...马马虎虎吧。\n"NOR;
                if (per < 15)
                        str = RED"咦，长得和无盐有点相似耶。\n"NOR;
	}
	if( !str) str="";
	return str;
}
string gettof(object me, object ob)
{
	object weapon;
	string skill_type,parry_type;
	int attack_points;
        if( objectp(weapon = ob->query_temp("weapon")) )
        {
                skill_type = weapon->query("skill_type");
                parry_type = "parry";
        }
        else
        {
                skill_type = "unarmed";
                parry_type = "unarmed";
        }

        attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	return  tough_level(attack_points);
}

string inventory_look(object obj, int flag)
{
	string str;

	str = obj->short();
	if( obj->query("equipped") )
		str = CYN "  √" NOR + str;
	else if( !flag )
		str = "    " + str;
	else
		return 0;

	return str;
}


string tough_level(int power)
{

	int lvl;
	int rawlvl;
	int grade = 1;
	if(power<0) power=0;
	rawlvl = (int) pow( (float) 1.0 * power, 0.3);
	lvl = to_int(rawlvl/grade);
                        if( lvl >= sizeof(tough_level_desc) )
                                lvl = sizeof(tough_level_desc)-1;
                        return tough_level_desc[((int)lvl)];
}

string getdam(object me, object obj)
{
	int level;
	object weapon;
	string skill_type;

	if( objectp(weapon = obj->query_temp("weapon")) )
		skill_type = weapon->query("skill_type");
	else
		skill_type = "unarmed";

	level = COMBAT_D->skill_power(obj, skill_type, SKILL_USAGE_ATTACK);
	level = level / 500000;
	if( level >= sizeof(heavy_level_desc) )
		level = sizeof(heavy_level_desc)-1;
	if (level<0) level = 0;
	return heavy_level_desc[((int) level)];
}

int help (object me)
{
	write(@HELP
指令格式: look [<物品>|<生物>|<方向>]
 
这个指令让你查看你所在的环境、某件物品、生物、或是方向。
 
HELP
);
	return 1;
}
