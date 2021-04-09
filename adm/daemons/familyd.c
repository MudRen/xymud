//负责存放各门派之间的“友好度”。
//Qyz
#include <ansi.h>
inherit F_SAVE;

#define FAMILY_ENEMY    2
#define FAMILY_FRIEND   1

//将军府→龙宫→火云洞→大雪山→普陀→月宫→百花谷→五庄观→蜀山→无底洞→盘丝→方寸→地府→将军府
nosave mapping family_xk =([
    "将军府"	: "东海龙宫",
    "东海龙宫"  : "火云洞",
    "火云洞"    : "大雪山",
    "大雪山"    : "南海普陀山",
    "南海普陀山": "月宫",
    "月宫"	: "百花谷",
    "百花谷"	: "五庄观",
    "五庄观"    : "蜀山派",
    "蜀山派"    : "陷空山无底洞",
    "陷空山无底洞": "盘丝洞",
    "盘丝洞"    : "方寸山三星洞",
    "方寸山三星洞": "阎罗地府",
    "阎罗地府"  : "将军府",
]);

mapping Family;

nosave mapping family_wx = ([
    "将军府"	: "土",
    "东海龙宫"  : "水",
    "火云洞"    : "火",
    "大雪山"    : "金",
    "南海普陀山": "木",
    "月宫"	: "土",
    "百花谷"	: "水",
    "五庄观"    : "火",
    "蜀山派"    : "金",
    "陷空山无底洞": "土",
    "盘丝洞"    : "木",
    "方寸山三星洞": "金",
    "阎罗地府"  : "火",
]);

nosave mapping Ranks = ([
	"bonze"  : ({ " 沙  弥 "," 比  丘 "," 和  尚 "," 大  师 ","%s大师"," 长  老 ","%s长老"," 金  刚 ","%s金刚"," 罗  汉 ","%s罗汉"," 声  闻 ","%s声闻"," 菩  萨 ","%s菩萨"," 佛  陀 ","%s佛"," 佛  祖 ", }),
	"bonze2" : ({ " 沙弥尼 "," 比丘尼 ","%s尼",    " 师  太 ","%s师太"," 长  老 ","%s长老"," 金  刚 ","%s金刚"," 罗  汉 ","%s罗汉"," 声  闻 ","%s声闻"," 菩  萨 ","%s菩萨"," 佛  陀 ","%s佛"," 佛  祖 ", }),
	"taoist" : ({ " 黄  冠 "," 炼  师 ","%s道人"," 道  长 ","%s道长"," 法  师 ","%s法师"," 玄  师 ","%s玄师"," 天  师 ","%s天师"," 上  人 ","%s上人"," 真  人 ","%s真人"," 天  尊 ","%s天尊"," 道  祖 ", }),
	"taoist2": ({ " 女  冠 "," 女炼师 ","%s道人"," 道  姑 ","%s道姑"," 女法师 ","%s法师"," 女玄师 ","%s玄师"," 女天师 ","%s天师"," 女上人 ","%s上人"," 女真人 ","%s真人"," 天  尊 ","%s天尊"," 道  祖 ", }),
	"yaomo"  : ({ " 小  妖 "," 妖  士 "," 妖  兵 "," 妖  将 ","%s将军"," 妖  王 ","%s大王"," 老  祖 ","%s老祖"," 天  妖 ","%s天妖"," 大  圣 ","%s大圣"," 妖  帝 ","%s妖帝"," 妖  师 ","%s妖师"," 妖  祖 ", }),
	"yaomo2" : ({ " 小妖精 "," 女妖士 "," 女妖兵 "," 女妖将 ","%s将军"," 女妖王 ","%s大王"," 老  祖 ","%s老祖"," 女天妖 ","%s天妖"," 大  圣 ","%s大圣"," 女妖帝 ","%s妖帝"," 妖  师 ","%s妖师"," 妖  祖 ", }),
	"ghost"  : ({ " 小  鬼 "," 游  魂 ","%s鬼"," 鬼  卒 "," 无  常 ","%s无常"," 判  官 ","%s判官"," 天  鬼 ","%s天鬼","大力鬼王"," 冥  王 ","%s冥王"," 冥  帝 ","%s冥帝"," 冥  师 ","%s冥师"," 冥  祖 ", }),
	"ghost2" : ({ " 女  鬼 "," 幽  魂 ","%s魂"," 鬼  女 "," 勾  魂 ","%s勾魂"," 鬼  婆 ","%s婆"," 女天鬼 ","%s天鬼","地府女主"," 冥  王 ","%s冥王"," 冥  帝 ","%s冥帝"," 冥  师 ","%s冥师"," 冥  祖 ", }),
	"xian"	 : ({ " 金  童 "," 侍  仙 "," 天  兵 ","%s天兵","%s天将"," 仙  官 ","%s仙官 "," 星  君 ","%s星君"," 大  仙 ","%s大仙"," 真  君 ","%s真君"," 天  王 ","%s天王"," 天  帝 ","%s大帝"," 圣  人 ",}),
	"xian2"	 : ({ " 玉  女 "," 女侍仙 "," 仙  女 ","%s仙女","%s仙子"," 仙  妃 ","%s仙妃 "," 女星君 ","%s星君"," 天  仙 ","%s天仙"," 真  君 ","%s真君"," 女  神 ","%s女神"," 娘  娘 ","%s娘娘"," 圣  人 ",}),
	"dragon" : ({ " 蜉  蝣 "," 虾  兵 "," 蟹  将 ","巡海夜叉","%s夜叉"," 海  将 "," 海  帅 ","%s*海帅"," 海  相 ","%s海相"," 龙  子 ","%s龙子"," 河龙王 "," 龙  王 ","%s龙王"," 龙  神 ","%s龙神"," 龙  祖 ",}),
	"dragon2": ({ " 蜉  蝣 "," 宫  娥 "," 蚌  女 "," 女夜叉 ","%s夜叉"," 女海将 "," 海  妃 ","%s*海妃"," 美人鱼 ","%s人鱼"," 龙  女 ","%s龙女"," 河龙王 "," 龙  王 ","%s龙王"," 龙  神 ","%s龙神"," 龙  祖 ",}),
	"fighter": ({ " 布  衣 "," 执戟长 ","%s校尉","%s骑将","%s中郎将","%s将军","%s大将军"," 战  仙 ","%s战仙"," 天  将 ","%s天将"," 天  王 ","%s天王"," 战  神 ","%s战神"," 战  圣 ","%s战圣"," 兵  祖 ",}),
	"fighter2":({ " 布  衣 "," 执戟长 ","%s校尉","%s骑将","%s中郎将","%s将军","%s大将军"," 战  仙 ","%s战仙"," 天  将 ","%s天将"," 天  王 ","%s天王"," 战  神 ","%s战神"," 战  圣 ","%s战圣"," 兵  祖 ",}),
	"other"  : ({ " 百  姓 "," 练气士 ","%s士"," 散  人 ","%s散人"," 法  师 ","%s法师"," 玄  师 ","%s玄师"," 天  师 ","%s天师"," 上  人 ","%s上人"," 真  人 ","%s真人"," 天  尊 ","%s天尊"," 道  祖 ", }),
	"scholar": ({ " 童  生 "," 贡  生 "," 举  人 "," 进  士 "," 鼎  甲 "," 学  士 "," 通  人 "," 鸿  儒 "," 高  望 "," 文  豪 ","文魁星"," 笔仙 ","%s仙"," 圣  贤 "," %s贤人"," 夫  子 ","%s夫子"," 圣  人 ",}), 
	"scholar2":({ " 女童生 "," 女贡生 "," 女举人 "," 女进士 "," 女鼎甲 "," 女学士 "," 女通人 "," 鸿  儒 "," 高  望 "," 女文豪 ","文魁星"," 笔仙 ","%s仙"," 圣  贤 "," %s贤人"," 夫  子 ","%s夫子"," 圣  人 ",}), 
]);


void create()
{
    seteuid(getuid());
    if( !restore() && !mapp(Family) )
        Family = ([]);
}

int remove()
{
    save();
    return 1;
}

string query_rank(object who)
{
	int lvl;
	string cls;
	if( !who )
		return 0;
	if( !stringp(cls = who->query("class")) )
		cls = "other";
	else if( cls=="dance" )
		return " 舞  姬 ";
	else
	{
		if( who->query("gender")=="女性" )
			cls = cls+"2";
		if( undefinedp(Ranks[cls]) )
			return " 百  姓 ";
	}
	lvl = who->query_level();
	if( lvl<10 )		return Ranks[cls][0];
	else if( lvl<40 )	return Ranks[cls][1];
	else if( lvl<50 )	return Ranks[cls][2];
	else if( lvl<60 )	return Ranks[cls][3];
	else if( lvl<70 )	return Ranks[cls][4];
	else if( lvl<80 )	return Ranks[cls][5];
	else if( lvl<90 )	return Ranks[cls][6];
	else if( lvl<100 )	return Ranks[cls][7];
	else if( lvl<110 )	return Ranks[cls][8];
	else if( lvl<120 )	return Ranks[cls][9];
	else if( lvl<130 )	return Ranks[cls][10];
	else if( lvl<140 )	return Ranks[cls][11];
	else if( lvl<150 )	return Ranks[cls][12];
	else if( lvl<160 )	return Ranks[cls][13];
	else if( lvl<170 )	return Ranks[cls][14];
	else if( lvl<180 )	return Ranks[cls][15];
	else if( lvl<190 )	return Ranks[cls][16];
	else	return Ranks[cls][17];
}

int perform_score(object ob,string skill)
{
	int pp = 0;
	string fam;
	if( !ob || !living(ob) )
		return 0;
	fam = ob->query("family/family_name");
    	if( !fam || !stringp(fam) )
    		return 0;
        switch(fam)
        {
		case "月宫" : 
                	if( (skill=="sword" && ob->query_skill_mapped("sword")=="snowsword")
                 	 || (skill=="whip" && ob->query_skill_mapped("whip")=="jueqingbian") )
            			pp+= (ob->query_skill("moondance",1)-100)/50;
            		break;
        	case "南海普陀山" :
            		if( (skill=="staff" && ob->query_skill_mapped("staff")=="lunhui-zhang")
             		|| (skill=="blade" && ob->query_skill_mapped("blade")=="cibeidao") )
            			pp+= (ob->query_skill("lotusforce", 1)-100)/80;
            		break;
        	case "阎罗地府" :
        		if( ob->query("bellicosity")>=500 )
        			pp+= ob->query("bellicosity")/80;
            		break;
        	case "方寸山三星洞" :
            		pp+= ob->query_skill("liangyi-sword",1)/70;
            		break;
        	case "大雪山" :
            		pp+= ob->query_skill("throwing",1)/60;
            		break;
        	case "将军府" :
            		pp+= ob->query_skill("yanxing-steps",1)/90;
            		break;
        	case "盘丝洞" :
            		pp+= ob->query_skill("zhuyan",1)/50;
            		break;
        	case "百花谷" :
        		pp+= ob->query_skill("zhuyan",1)/60;   
        		break;
            	case "陷空山无底洞" :
                	if( ob->query_temp("zxzx") )
            			pp+= ob->query_skill("lingfu-steps",1)/50;
        		break;    
        	case "火云洞" :
        		pp+= (ob->query_skill("pingtian-dafa",1)-150)/50;
        		break;
		case "东海龙宫" :
                	if( (skill=="fork" && ob->query_skill_mapped("fork")=="fengbo-cha")
                 	|| (skill=="unarmed" && ob->query_skill_mapped("unarmed")=="dragonfight") )
                		pp+= ob->query_skill("dragonforce")/50;
                	break;
            	case "蜀山派" :
                	pp+= ob->query_skill("yujianshu")/120;
                	break;
            	case "五庄观" :
                	pp+= (ob->query_skill("taiyi",1)-100)/50;
                	break;
                default : return 0;	
        }
        return pp;
}  	

//门派相克 1为克制 -1为被克
int family_restrain(object me,object victim)
{
	if( !me || !victim )
        	return 0;
    	if( !me->query("family/family_name")
     	 || !victim->query("family/family_name") )
        	return 0;
	if( me->query("family/family_name")==victim->query("family/family_name") )
		return 0;        	
        if( undefinedp(family_xk[victim->query("family/family_name")]) )
        	return 0;
        if( undefinedp(family_xk[me->query("family/family_name")]) )
        	return 0;
        if( family_xk[me->query("family/family_name")]==victim->query("family/family_name") )
        	return 1;
        else if( family_xk[victim->query("family/family_name")]==me->query("family/family_name") )
        	return -1;		
    	else	return 0;
}

int family_relation(string your_fam,string my_fam )
{
        return 0;
}

string query_save_file() { return DATA_DIR + "familyd"; }

int set_relation(string my_fam, mapping relation)
{
    Family[my_fam] = relation;
    save();
    return 1;
}

int add_family_enemy( string my_fam, string name, int score )
{
    if( !Family || undefinedp( Family[my_fam] ) )
        Family[my_fam] = ([ name : score ]);
    if( !undefinedp(Family[my_fam][name] ) )
        Family[my_fam][name] += score;
    else Family[my_fam] += ([ name : score ]);
    save();
    return 1;
}

int remove_family_enemy( string my_fam, string name )
{
    if( undefinedp( Family[my_fam] ) ) return 0;
    else if( !undefinedp( Family[my_fam][name] ) )
    {
        map_delete(Family[my_fam] , name);
        save();
	return 1;
    }
    else return 0;
}

int is_family_enemy( string my_fam, string name )
{
    if( undefinedp( Family[my_fam] )) return 0;
    else if( !undefinedp( Family[my_fam][name])&&Family[my_fam][name]>100)
        return 1;
    else return 0;
}

int query_enemy_quantity( string my_fam, string name )
{
    if( undefinedp( Family[my_fam] )) return 0;
    else if( !undefinedp( Family[my_fam][name] ) )
        return Family[my_fam][name];
    else return 0;
}
        
mapping query_relation(string my_fam)
{
    if( !undefinedp(Family[my_fam]) )
        return Family[my_fam];
    else
        return ([]);
}

int deal_family_relation( object victim, object killer )
{
	return 0;
}

void clear_all_family_relation( string id )
{
}

int leave_family(object who,object npc)
{
	string *masters,data,str,skill_force,skill_spells;
	int wx;
	if( !who || !npc )
		return 0;
	if( !living(npc) || userp(npc) )
		return 0;
	if( !who->query_temp("betray") || !present(who,environment(npc)) )
		return 0;
	if( !str=npc->query("family/family_name") )
		return 0;
	masters = ({
        	"南海普陀山","阎罗地府","方寸山三星洞","月宫",
        	"大雪山","五庄观","东海龙宫","将军府","火云洞",
        	"陷空山无底洞","蜀山派","盘丝洞","百花谷","散仙派",
	});
		
	//不在familyd控制的门派		
	if( member_array(str,masters)==-1 )
	{
		tell_object(who,npc->name()+"向你微一稽首，道：这位道友，我"+str+"不在归化之列，还望道友告知圣人。\n");
		return 0;
	}
	if( !who->query("family/family_name")
	 || who->query("family/family_name")!=str )
	{
		tell_object(who,npc->name()+"向你微一稽首，道：这位道友非我"+str+"门人，所为何事？\n");
		return 0;
	}
	if( npc->query_skill("force",1)<1 
         && npc->query_skill("spells",1)<1 )
	{
		tell_object(who,npc->name()+"向你微一稽首，道：这位道友，"+RANK_D->query_self(npc)+"无此功德。\n");
		return 0;
	}
	skill_force=npc->query_skill_mapped("force");
	skill_spells=npc->query_skill_mapped("spells");
	if( !skill_force || !stringp(skill_force)
	 || !skill_spells || !stringp(skill_spells) )
	{
		tell_object(who,npc->name()+"向你一稽首，道：这位道友，"+RANK_D->query_self(npc)+"无此功德。\n");
		return 0;
	}
	message_vision(CYN"$N"CYN"对$n"CYN"说道：既是你与"+str+"无缘，你便下山去吧！\n"NOR,npc,who);
	
	data = str;
	
	who->add("betray/count", 1);
	who->add("betray/"+data, 1);
	
	wx = who->query("daoxing");
	if( wx>10000 )
		wx = wx/100*80;
	else	wx = wx*80/100;	
	who->set("daoxing",wx);
	CHANNEL_D->do_channel(npc,"chat","今"+who->query("name")+"脱离吾"+str+"，各安天命。");	
	who->delete_skill(skill_force);
	who->delete_skill(skill_spells);
	("/cmds/std/enable.c")->main(who,"force none");
	("/cmds/std/enable.c")->main(who,"spells none");
	who->delete("family");
	who->delete("class");
	who->set("faith",0);
	who->set("title", "普通百姓");
	who->set_temp("betray", 0);
	who->delete("shilian");
	who->save(1);
	npc->command("say 圣人无情，善恶无形，汝此去好自为之。。。\n");
	return 1;
}
	
string family_wuxing(object who)
{
	string fam;
	fam = who->query("family/family_name");
	if( !fam )
		return "NONE";
	if( undefinedp(family_wx[fam]) )
		return "NONE";
	return	family_wx[fam];
}

//开除使用
int expell_family(object me)
{
	int dx,i;
	string fam,*skills;
	mapping mp_skill = ([
		"阎罗地府"	: ({"gouhunshu","tonsillit",}),
		"五庄观"	: ({"taiyi","zhenyuan-force",}),
		"火云洞"	: ({"huomoforce","pingtian-dafa",}),
		"方寸山三星洞"	: ({"dao","wuxiangforce",}),
		"将军府"	: ({"baguazhou","lengquan-force",}),
		"蜀山派"	: ({"tianshi-fufa","xianfeng-yunti",}),
		"百花谷"	: ({"brightjade-force","baihua-xianfa",}),
		"盘丝洞"	: ({"jiuyin-xinjing","pansi-dafa",}),
		"月宫"		: ({"moonshentong","moonforce",}),
		"东海龙宫"	: ({"dragonforce","seashentong",}),
		"大雪山"	: ({"ningxie-force","dengxian-dafa",}),
		"陷空山无底洞"	: ({"huntian-qigong","yaofa",}),
		"南海普陀山"	: ({"buddhism","lotusforce",}),
	]);
	if( !me || !userp(me) )
		return 0;
	fam = me->query("family/family_name");
	if( !fam || !stringp(fam) || member_array(fam,keys(mp_skill))==-1 )
		return 0;
	dx = me->query("daoxing");
	if( dx>10000 )
		dx = dx/100*70;
	else	dx = dx*70/100;
	me->set("daoxing",dx);
	skills = mp_skill[fam];
	for(i=0;i<sizeof(skills);i++)
		me->delete_skill(skills[i]);
	("/cmds/std/enable.c")->main(me,"force none");
	("/cmds/std/enable.c")->main(me,"spells none");	
	me->add("betray/count", 1);
	me->add("betray/"+fam, 1);
	me->set("faith",0);
	me->delete("shilian");
	me->save();
	return 1;
}

int shentong_combat_ap(object me,object victim,int ap)
{
	int pp;
	if( !me || !victim || ap<=0 )
		return 0;	
/*
通幽-克制阎罗地府 驱神-克制南海普陀山 担山-克制火云洞 禁水-克制东海龙宫 掩日-克制将军府
取月-克制月宫 煮石-克制方寸山三星洞 吞刀-克制陷空山无底洞 壶天-克制五庄观
祈晴-克制大雪山 坐火-克制百花谷 隐形-克制蜀山 指化-克制盘丝洞 斩妖-克制yaomo|tianmo
*/			
	if( victim->query("family/family_name")=="陷空山无底洞"
         && me->query_skill("tundao",2)>100 )
	{
		pp = me->query_skill("tundao",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	if( victim->query("family/family_name")=="阎罗地府"
         && me->query_skill("tongyou",2)>100 )
	{
		pp = me->query_skill("tongyou",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	if( victim->query("family/family_name")=="南海普陀山"
         && me->query_skill("qushen",2)>100 )
	{
		pp = me->query_skill("qushen",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	if( victim->query("family/family_name")=="火云洞"
         && me->query_skill("danshan",2)>100 )
	{
		pp = me->query_skill("danshan",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	if( victim->query("family/family_name")=="东海龙宫"
         && me->query_skill("jinshui",2)>100 )
	{
		pp = me->query_skill("jinshui",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	if( victim->query("family/family_name")=="将军府"
         && me->query_skill("yanri",2)>100 )
	{
		pp = me->query_skill("yanri",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	if( victim->query("family/family_name")=="月宫"
         && me->query_skill("qu-yue",2)>100 )
	{
		pp = me->query_skill("qu-yue",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}		
	if( victim->query("family/family_name")=="方寸山三星洞"
         && me->query_skill("zhushi",2)>100 )
	{
		pp = me->query_skill("zhushi",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	if( victim->query("family/family_name")=="百花谷"
         && me->query_skill("zuohuo",2)>100 )
	{
		pp = me->query_skill("zuohuo",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	if( victim->query("family/family_name")=="五庄观"
         && me->query_skill("hutian",2)>100 )
	{
		pp = me->query_skill("hutian",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}		
	if( victim->query("family/family_name")=="大雪山"
         && me->query_skill("qiqing",2)>100 )
	{
		pp = me->query_skill("qiqing",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	if( victim->query("family/family_name")=="蜀山派"
         && me->query_skill("yinxing",2)>100 )
	{
		pp = me->query_skill("yinxing",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	if( victim->query("family/family_name")=="盘丝洞"
         && me->query_skill("zhihua",2)>100 )
	{
		pp = me->query_skill("zhihua",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	//斩妖 克制class yaomo|tianmo
	if( (victim->query("class")=="yaomo"||victim->query("class")=="tianmo")
         && me->query_skill("zhanyao",2)>100 )
	{
		pp = me->query_skill("zhanyao",1);
		pp/= 100;
		if( pp>25 )
			pp = 25;
		ap = ap*(100+pp)/100;
	}
	return ap;
}		