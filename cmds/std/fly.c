//cglaem...12/17/96.
// modify by windle 2006-6-24

#include <ansi.h>
#include "/cmds/std/valid_move.h"
string *fly_up_msg = 
({
        RED"只见$N口中念动有词，忽然双臂一振，空中雷轰电掣黑雾漫漫，但见电光飞闪$N随之消失…… \n\n"NOR,
        HIR"$N撮唇吹了一个响哨，一匹神骏的宝马随声而至，$N纵身上马，绝尘而去…… \n\n"NOR,
        HIB"$N往黑暗处一指，只见所指之处仿佛出现一扇门，$N大步走入，门也随之消失…… \n\n"NOR,
        HIG"$N捻个口诀，口中念动真言，只见祥光万道，白雾紫气，红云腾腾而起,$N纵身跃上，飞驰而去......\n\n"NOR,
        HIM"$N妩媚一笑，欣然起舞，随着一阵花香，已消失在月光中……\n"NOR,
        HIW"$N伸手一招，一朵莲花平地而起,$N坐上莲台，转眼而去……\n"NOR,
        MAG"$N把口一张，吐出一道七色神光，笼罩其身，但见霞光一闪,$N化作一道彩虹消失的无影无踪……\n"NOR,
        HIB"$N大袖一摆，平地起身，只见风起云涌，$N在空中连踏出乾坤八位，几步踏出，身形已然消失……\n"NOR,
        HIW"$N随手一挥，阴风簇拥，一派寒雾笼罩真身，旋转而去…… \n"NOR,
        HIY"$N口中念着佛号，脚下升起一朵莲花宝座，缓缓离地飞去……  \n"NOR,
        HIC"$N口摇身一变，现出原形，正是一条神龙，随即穿云而去…… \n"NOR,
        RED"$N口捻个口诀，口中念动真言,突然“轰”地冒起一团红雾,$N随即隐入红雾中。\n"NOR,
        HIR"只见万道霞光散过,$N踏着七朵彩云腾空而去……\n"NOR,
        HIC"$N口捻个口诀，扔出一把宝剑，$N飞驰而上，一招「御剑飞行」向远方飞去。。。。\n"NOR,
        HIY"只见$N手指一扬，纷纷花瓣有如花雨落下，$N的身形也渐渐消失在花雨中.....\n"NOR,
        HIR"$N念了几声咒语，周围冒起一团团火焰，火焰一闪，$N消失在火光之中。\n\n"NOR,
HIG"$N"HIR"手"HIB"一"HIM"指"HIY"，"HIC"招"HIB"来"HIC"一"HIG"道"HIB"彩"HIR"虹"HIM"，"HIW"小"HIC"心"HIR"翼"HIG"翼"HIB"的"HIY"爬"HIC"了"HIM"上"HIR"去"HIG"。\n\n"NOR,
        HIG"$N手一指，招来一道彩虹，小心翼翼的爬了上去。\n\n"NOR,
});


string *fly_down_msg = 
({
        RED"\n忽然间悲风飒飒，惨雾迷迷，阴云四合，风过数阵，“啪”的一股黑烟升起,$N%s从黑烟中走了出来…… \n"NOR,
        HIR"\n 震耳欲聋的一声：“本将在此！”，$N已来到大家眼前。\n"NOR,
        HIB"\n悲风四起，杀气漫空，黑暗暗俱是些鬼哭神嚎，伴随着冷森森的笑声，$N%s如魑魅般从黑暗中出现…… \n"NOR,
        HIG"\n忽听得空中有一阵异香仙乐，飘飘而来,空中飘落一朵七彩祥云，$N%s拨开云端走了出来……。\n"NOR,
        HIM"\n只听得半空中仙乐齐鸣，垂珠璎珞，一阵香风缥渺，异味芳馨氤氲，$N%s飘然而至…… \n"NOR,
        HIW"\n忽然一朵莲花降下，$N走了出来。 \n"NOR,
        MAG"\n但见霞光万道，瑞彩千条，光婵灿烂，映目射眼，一道彩虹从天空划过，$N%s随彩虹飘然而至…… \n"NOR,
        HIB"\n一阵清风吹来，$N%s从空中降落…… \n"NOR,
        HIW"\n霎时间，大雪纷飞，雪花翩翩如雾卷云腾，冷气侵人，$N%s亦如晶莹剔透的雪花随风飘下…… \n"NOR,
        HIY"\n刹那间祥云缭绕，佛光万丈，莲花万朵，络绎不断，$N%s踏着莲花宝座，徐徐降落尘间………\n"NOR,
        HIC"\n但见云光缥缈，半空中仿佛冲出一条水柱，$N%s从水柱上稳稳跳落地下……  \n"NOR,
        RED"\n一团红色的烟雾涌了过来,$N%s突然从里面蹦了出来. \n"NOR,
        HIB"\n$N%s踏着七朵彩云从天而降,喃喃说了几句：本散仙要PK了! \n"NOR,
        HIC"\n一道蓝光闪过,$N%s从剑上跳了下来。 \n"NOR,
        HIY"\n随着一阵花香飘过，$N的身影出现在一阵花雨中.....\n"NOR,
        RED"\n刹那间火光点点，慢慢凝成一团火焰，$N从火焰中信步走了出来。 \n"NOR,
         HIR"\n彩"HIM"虹"HIG"落"HIC"处"HIY","HIB"只"HIG"见"HIR"$N"HIC"从"HIG"上"HIM"面"HIB"高"HIY"高"HIM"兴"HIW"兴"HIC"地"HIG"滑"HIR"落"HIM"下"HIB"来"HIC"。\n\n"NOR,
        HIG"\n彩虹落处,只见$N从上面高高兴兴地滑落下来。\n\n"NOR,
});

string query_fabao_name(object fabao)
{
	if( !fabao )
		return "法宝";
	return COLOR_D->clean_color(fabao->query("name"));	
}

string fly_place(object me,string arg)
{
	string loc;
	object map;
	if( !me || !living(me) || !arg )
		return "";
	switch(arg)
	{
		case "stone"	: return "/d/dntg/hgs/entrance";
		case "aolai"	: return "/d/aolai/center";
		case "kaifeng"	: return "/d/kaifeng/tieta";
		case "moon"	: return "/d/moon/ontop2";
		case "lingtai"	: return "/d/lingtai/gate";
		case "putuo"	: return "/d/nanhai/gate";
		case "changan"	: return "/d/city/center";
		case "luoyang"	: return "/d/luoyang/center";
		case "sky"	: 
			if( me->query_level()<80 )
				return "";
			return "/d/dntg/sky/nantian";
		case "wuzhuang"	: return "/d/qujing/wuzhuang/gate";
		case "meishan"	: return "/d/meishan/erlangwai";
		case "baihuagu" : return "/d/baihuagu/huahai";
		case "gao"      : return "/d/gao/gate";
		case "psd"	: return "/d/pansi/tao_in";
		//case "shennong"	: return "/d/liandan/road1";
		case "shushan"	: return "/d/shushan/road1";
		case "penglai"	: 
                	if(!(map=present("eastsea map", me)) && !wizardp(me)) 
                        	return "";
                	if( !wizardp(me)&&(string)map->query("unit")!="张" )
                        	return "";
			return "/d/penglai/penglai";
		case "xueshan"	:
                	if((string)me->query("family/family_name")!="大雪山") 
                	{
                		if(!(map=present("xueshan map", me)) && !wizardp(me)) 
                			return "";
                		if( !wizardp(me)&&(string)map->query("unit")!="张" )
                			return "";
                	}		
                	return "/d/xueshan/binggu";
		case "baoxiang"	: return sprintf("/d/qujing/baoxiang/bei%d",1+random(4));
		case "pingding"	: return sprintf("/d/qujing/pingding/ping%d",1+random(4));
		case "yalong"	: return sprintf("/d/qujing/pingding/yalong%d",1+random(3));
		case "wuji"	: return "/d/qujing/wuji/square.c";
                case "chechi"	: return sprintf("/d/qujing/chechi/jieshi%d",1+random(9));
		case "tongtian"	: return sprintf("/d/qujing/tongtian/hedong%d",1+random(6));
		case "jindou"	: return sprintf("/d/qujing/jindou/jindou%d",1+random(4));
		case "nuerguo"	: 
			loc = "/d/qujing/nuerguo/towna1.c";
                	loc[strlen(loc)-4] = 'a'+random(3);
                	loc[strlen(loc)-3] = '1'+random(3);
                	return loc;
                case "dudi"	: return sprintf("/d/qujing/dudi/dudi%d",1+random(4));
                case "firemount": return sprintf("/d/qujing/firemount/cuiyun%d",1+random(5));
                case "jilei"	: return sprintf("/d/qujing/jilei/jilei%d",1+random(3));
                case "jisaiguo"	: return sprintf("/d/qujing/jisaiguo/east%d",1+random(4));
                case "jingjiling" : return "/d/qujing/jingjiling/jingji1.c";
                case "xiaoxitian" : return "/d/qujing/xiaoxitian/simen.c";
                case "zhuzi"	: return sprintf("/d/qujing/zhuzi/zhuzi%d",1+random(5));
                case "qilin"	: return "/d/qujing/qilin/yutai.c";
                case "pansi"	: return "/d/qujing/pansi/ling1.c";
                case "liusha"	: return "/d/qujing/liusha/riverside.c";
                case "heifeng"	: return "/d/qujing/heifeng/road4.c";
                case "yingjian"	: return "/d/qujing/yingjian/lakeside3.c";
                case "yunzhan"	: return "/d/qujing/yunzhan/shanlu1.c";
                case "shuangcha": return "/d/qujing/shuangcha/shanlu3.c";
                case "sisheng"	: return "/d/qujing/village/cunkou.c";
                case "huangfeng": return "/d/qujing/huangfeng/dongkou.c";
                case "biqiu"	: return sprintf("/d/qujing/biqiu/jie%d",1+random(9));
		case "qinghua"	: return "/d/qujing/biqiu/zhuang.c";
		case "wudidong" : return sprintf("/d/qujing/wudidong/firemount-wudidong%d",1+random(3));
		case "qinfa"	: return sprintf("/d/qujing/qinfa/jiedao%d",1+random(8));
		case "yinwu"	: return "/d/qujing/yinwu/huangye1.c";
		case "fengxian" : return sprintf("/d/qujing/fengxian/jiedao%d",1+random(9));
		case "yuhua"	: return sprintf("/d/qujing/yuhua/xiaojie%d",1+random(9));
		case "baotou"	: return sprintf("/d/qujing/baotou/shanlu%d",1+random(9));
		case "zhujie"	: return sprintf("/d/qujing/zhujie/shanlu1%d",1+random(8));
		case "jinping"	: return sprintf("/d/qujing/jinping/xiaojie%d",1+random(7));
		case "qinglong" : return "/d/qujing/qinglong/shanjian.c";
		case "tianzhu"	: return sprintf("/d/qujing/tianzhu/jiedao1%d",1+random(8));
		case "maoying"	: return sprintf("/d/qujing/maoying/shanpo%d",1+random(9));
		case "lingshan"	: return sprintf("/d/qujing/lingshan/dalu%d",1+random(3));
		default : return "";
	}	
}                		

int main(object me, string arg)
{
        string loc;
        int mana_cost,p;
        object fabao,ridee, map;
        string ridemsg;
        string family;
        string msg = "_";

        seteuid(getuid());
        if( me->is_fighting() )
                return notify_fail("你正在战斗，飞不开。\n");
        if( me->is_busy() || me->query_temp("pending/exercising"))
                return notify_fail("你正忙着呢，没工夫腾云驾雾。\n");
        if( !wizardp(me) && !environment(me)->query("outdoors") )
                return notify_fail("周围没有一片云，没办法腾云驾雾。\n");
        if( me->is_ghost() )
                return notify_fail("做了鬼了，就老实点吧！\n");
        if( environment(me)->query("short") == HIR"CS休息室"NOR )
         return notify_fail("你还是先呆着吧\n");
        if( !arg )
                return notify_fail("你要飞到哪里去？\n");
        if( !valid_move(me) ) 
            return notify_fail("你被定住了，哪里飞得起来！\n");
        if( (int)me->query("sen") * 100 / (int)me->query_maxsen() < 50 )
                return notify_fail("你现在头脑不太清醒，当心掉下来摔死。\n");
        if( (int)me->query("kee") * 100 / (int)me->query_maxkee() < 50 )
                return notify_fail("你想飞起来，可是体力似乎有点不支。\n");
	if( (int)me->query("mana") < 50 )
        {
                message_vision(HIY"$N"HIY"奋力望上一跳，似乎想飞起来。结果离地不到三尺就一个倒栽葱摔了下来。\n"NOR, me);
                return notify_fail("你目前法力不够充盈。\n");
        }
        loc = fly_place(me,arg);
	if( me->query_temp("shushan_fly") 
	 && me->query("family/family_name")=="蜀山派" )
	{
		if( !stringp(msg=me->query_temp("shushan_fly_msg")) )
			msg = "宝剑";
		message_vision(HIC"\n$N"HIC"一掐剑诀，脚下"+msg+HIC"霞光一闪，仿佛有灵性一般，似一道飞虹般带着$N"HIC"飞弛而出！\n\n"NOR,me);	
		if( !loc || loc=="" )
        	{
        		write("你在天上转了半天也不知该往那边飞。。。\n");
                	message_vision("\n$N失望地驾驭着"+msg+"从半空跳了下来！\n", me);
                	return 1;
		}
		if(MISC_D->random_capture(me,0,1)) 
			return 1;
		me->move(loc);
		message_vision(HIC"\n半空霞光一闪，"+msg+HIC"已带着$N"HIC"从云层中直冲而下，离地三寸，立刻平稳的定住了。\n"NOR,me);
		tell_object(me,HIY"【系统】你的「"HIG"御剑飞行术"HIY"」状态已消失。"NOR"\n");
		message_vision("$N一掐剑诀，收回了"+msg+"。\n",me);
		p = me->query_temp("shushan_fly");
		me->add_temp("apply/dodge",-p);
		me->add_temp("apply/attack",-p);
		me->delete_temp("shushan_fly_msg");
		me->delete_temp("shushan_fly");
		return 1;
	}        
        //法宝飞行
	if( objectp(fabao=me->query_temp("armor/Fabao"))
         && fabao->query_temp("jiing")
	 && fabao->query("飞行") )
	{		
		if( !stringp(msg=fabao->query("fabao/fly_msg"))
		  || strlen(msg)<2 )
			msg = HIC"\n$N"HIC"口中念了几句咒语，只见$n"HIC"上忽绽道道霞光，包裹住$N"HIC"直冲天际而去！\n\n"NOR;
		msg = replace_string(msg,"$n",query_fabao_name(fabao));	
		message_vision(msg,me);	
		if( !loc || loc=="" )
        	{
        		write("你在天上转了半天也不知该往那边飞。。。\n");
                	message_vision("\n"HIC"$N失望地驾驭着"+query_fabao_name(fabao)+HIC"从半空跳了下来！\n"NOR, me);
                	me->add("mana",-20);
                	return 1;
		}
		if(MISC_D->random_capture(me,0,1)) 
			return 1;
		me->move(loc);
		if( !stringp(msg=fabao->query("fabao/fly_msg2"))
		  || strlen(msg)<2 )
			msg = HIC"\n一道霞光从半空落将下来，待到霞光散去，$N"HIC"从中显出了身影。\n\n"NOR;
		msg = replace_string(msg,"$n",query_fabao_name(fabao));		
		message_vision(msg,me);	
		me->add("mana",-50);
		return 1;	
	}
	else if( me->query_level()<80 && !wizardp(me) )	 
		return notify_fail("你境界不够，还不能肉身飞行，还是依赖法宝吧。\n");
        //end
	family = me->query("family/family_name");
	switch( family )
        {
	        case "陷空山无底洞"     : message_vision(fly_up_msg[0 ], me);break;
        	case "将军府"           : message_vision(fly_up_msg[1 ], me);break;
        	case "阎罗地府"         : message_vision(fly_up_msg[2 ], me);break;
        	case "方寸山三星洞"     : message_vision(fly_up_msg[3 ], me);break;
        	case "月宫"             : message_vision(fly_up_msg[4 ], me);break;
        	case "昆仑山玉虚洞"     : message_vision(fly_up_msg[5 ], me);break;
        	case "盘丝洞"           : message_vision(fly_up_msg[6 ], me);break;
        	case "五庄观"           : message_vision(fly_up_msg[7 ], me);break;
        	case "大雪山"           : message_vision(fly_up_msg[8 ], me);break;
        	case "南海普陀山"       : message_vision(fly_up_msg[9 ], me);break;
        	case "东海龙宫"         : message_vision(fly_up_msg[10], me);break;
        	case "火云洞"           : message_vision(fly_up_msg[11], me);break;
        	case "散仙派"           : message_vision(fly_up_msg[12], me);break;
        	case "蜀山派"           : message_vision(fly_up_msg[13], me);break;
        	case "百花谷"           : message_vision(fly_up_msg[14], me);break;
//        	case "火系魔法教派"     : message_vision(fly_up_msg[15], me);break;
        	default                 : message_vision(fly_up_msg[16], me);break;
        }
        mana_cost = 50;
        me->add("mana", -mana_cost);
        if( !loc || loc=="" )
        {
        	write("你在天上转了半天也不知该往那边飞。。。\n");
                message_vision("\n$N失望地从云上跳了下来！\n", me);
                return 1;
	}
        // mon /10/18/98
        if(MISC_D->random_capture(me,0,1)) return 1;
        if(ridee = me->ride()) 
        {
        	ridemsg = ridee->query("ride/msg")+"着"+ridee->name();
          	ridee->move(loc);
        }  
        else	ridemsg = "";
                                                        
        me->move(loc);
//       write("\n\n到了！你按下云头跳了下来。\n");

        family = me->query("family/family_name");
        switch( family )
        {
        case "陷空山无底洞"     : msg = sprintf( fly_down_msg[0 ], ridemsg); break;
        case "将军府"           : msg = sprintf( fly_down_msg[1 ], ridemsg); break;
        case "阎罗地府"         : msg = sprintf( fly_down_msg[2 ], ridemsg); break;
        case "方寸山三星洞"     : msg = sprintf( fly_down_msg[3 ], ridemsg); break;
        case "月宫"             : msg = sprintf( fly_down_msg[4 ], ridemsg); break;
        case "昆仑山玉虚洞"     : msg = sprintf( fly_down_msg[5 ], ridemsg); break;
        case "盘丝洞"           : msg = sprintf( fly_down_msg[6 ], ridemsg); break;
        case "五庄观"           : msg = sprintf( fly_down_msg[7 ], ridemsg); break;
        case "大雪山"           : msg = sprintf( fly_down_msg[8 ], ridemsg); break;
        case "南海普陀山"       : msg = sprintf( fly_down_msg[9 ], ridemsg); break;
        case "东海龙宫"         : msg = sprintf( fly_down_msg[10], ridemsg); break;
        case "火云洞"           : msg = sprintf( fly_down_msg[11], ridemsg); break;
        case "散仙派"           : msg = sprintf( fly_down_msg[12], ridemsg); break;
        case "蜀山派"           : msg = sprintf( fly_down_msg[13], ridemsg); break;
        case "百花谷"           : msg = sprintf( fly_down_msg[14], ridemsg); break;
        case "火系魔法教派"     : msg = sprintf( fly_down_msg[15], ridemsg); break;
        default                 : msg = sprintf( fly_down_msg[16], ridemsg); break;
        }
    	message_vision(msg, me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : fly|fei [目的地]

当你的道行和法力高强时，你可以腾云驾雾。

目前你可以飞到的地方：
changan         ->长安城                 kaifeng        ->开封城
luoyang		->洛阳城		 gao		->高老庄
stone           ->花果山仙石             sky            ->南天门
moon            ->昆仑山月宫             penglai        ->蓬莱仙岛
lingtai         ->灵台方寸山             putuo          ->南海普陀山
xueshan         ->大雪山寒冰谷           meishan        ->梅山灌江口
wuzhuang        ->万寿山五庄观           aolai          ->傲来国
baihuagu	->蓬莱山百花谷		 shushan	->蜀山派
psd		->盘丝洞

baoxiang        ->宝象国                 pingding       ->平顶山
yalong          ->压龙山                 wuji           ->乌鸡国
chechi          ->车迟国                 tongtian       ->通天河
jindou          ->金兜山                 nuerguo        ->女儿国
dudi            ->毒敌山                 firemount      ->火焰山
jilei           ->积雷山                 jisaiguo       ->祭赛国
jingjiling      ->荆棘岭                 xiaoxitian     ->小西天
zhuzi           ->朱紫国                 qilin          ->麒麟山
pansi           ->盘丝岭                 biqiu          ->比丘国 
qinghua         ->清华庄                 wudidong       ->无底洞
qinfa           ->钦法国                 fengxian       ->凤仙郡 
yinwu           ->隐雾山                 yuhua          ->玉华县 
baotou          ->豹头山                 zhujie         ->竹节山
jinping         ->金平府                 qinglong       ->青龙山 
tianzhu         ->天竺国                 maoying        ->毛颖山 
huangfeng       ->黄风岭                 heifeng        ->黑风山
guanyin         ->观音院                 yingjian       ->鹰愁涧
kusong          ->枯松涧                 sisheng        ->四圣山庄
shuangcha       ->双叉岭                 yunzhan        ->云栈洞
lingshan        ->灵山              

HELP
        );
        return 1;
}
