inherit ROOM;
#include <ansi.h>

mapping KillMsg2 = ([
//baihuagu
        "cast_flower" : "百花飞舞",
        "exert_hanyulingfeng" : "寒玉灵风",
        "perform_qingcheng" : "倾城一笑",
        "perform_changhong" : "长虹经天",
        "perform_jingshen" : "惊神一击",
        "perform_siji" : "四季飞花",
        "perform_wunian" : "无念无忧",
        "perform_zizai" : "自在逍遥",
        "perform_heng" : "横剑",
        "perform_newqijian" : "纵横七绝",
        "perform_yumei" : "雨激梅花半瓣香",
        "perform_zong" : "纵剑",
        "perform_zongheng" : "纵横四海",
//bonze
        "cast_bighammer" : "大力降魔杵",
        "cast_jinguzhou" : "紧箍咒",
        "perform_cibei" : "慈悲诀",
        "perform_lian" : "慈悲连环",
        "perform_lingxi" : "灵犀指",
        "perform_wanfo" : "万佛朝宗",
        "perform_wuzhi" : "五指连心",
        "perform_chaodu" : "超生渡化",
        "perform_fire" : "无妄之火",
        "perform_pudu" : "慈光普渡",
//dragon
        "perform_hlb" : "邪王炎杀黑龙波",
        "perform_leidong" : "雷动九天",
        "perform_shenglong" : "庐山升龙霸",
        "perform_sheshen" : "舍身技",
        "exert_roar" : "碧海龙吟",
        "perform_xiao" : "龙啸九天",
        "perform_bibo" : "碧波浪涌",
        "perform_dhwl" : "大海无量",
        "perform_break" : "混元一破",
        "cast_water" : "双龙水柱",
//fighter
        "cast_light" : "神霄电法符",
        "cast_poison" : "五瘟符",
        "cast_rain" : "神霄雨法符",
        "cast_thunder" : "神霄雷法符",
        "cast_wind" : "神霄风法符",
        "perform_bugong" : "不攻有悔",
        "perform_huima" : "回马枪",
        "perform_juanlian" : "珍珠倒卷帘",
        "perform_nine" : "绝命九枪",
        "perform_chong" : "冲字诀",
        "perform_hengsao" : "横扫千军",
        "perform_pofuchenzhou" : "破釜沉舟",
        "perform_jue" : "万刃神兵诀",
        "perform_kai" : "开天斧",
        "perform_nine" : "盘古九式",
        "perform_pidi" : "辟地斧",
        "perform_sanban" : "三板斧",
        "perform_duan" : "残魂断肢",
        "perform_andu" : "暗度陈仓",
        "perform_feijian" : "撒手锏",
        "perform_jingtian" : "惊天吼地",
        "perform_suomeng" : "锁梦缠魂",
        "perform_sheri" : "射日箭",
//ghost
        "cast_gouhun" : "勾魂术",
        "cast_inferno" : "地狱火",
        "cast_invocation" : "召唤鬼卒",
        "perform_ldlh" : "六道轮回",
        "perform_three" : "神·人·鬼",
        "perform_xingyun" : "鬼火腥云",
        "perform_zhua" : "无常爪",
        "perform_qmly" : "青面獠牙",
        "exert_sheqi" : "摄气诀",
        "perform_duoming" : "追魂夺命",
        "perform_souldrinker" : "油尽灯枯",
        "perform_yanluo" : "歌舞阎罗",
//moon
        "perform_flower" : "天女散花",
        "perform_changhen" : "长恨天歌",
        "perform_huixuan" : "绝情回旋",
        "perform_qingmang" : "青芒三式",
        "perform_sanshou" : "三无三不手",
        "perform_yixiao" : "倾城一笑",
        "cast_arrow" : "落日神箭",
        "cast_huimeng" : "回梦咒",
        "cast_invocation" : "召唤天兵",
        "cast_mihun" : "迷魂咒",
        "cast_shiyue" : "蚀月咒",
        "perform_dance" : "清歌妙舞",
        "perform_huifeng" : "回风剑",
        "perform_qin" : "倾城倾国",
        "perform_tian" : "漫天飞雪",
        "perform_duanfa" : "断发斩情",
//pansi
        "perform_haotan" : "痴情八叹",
        "perform_hongyan" : "红颜白发",
        "perform_juehu" : "九阴绝户手",
        "cast_love" : "召唤爱神",
        "cast_wuzhishan" : "五指山",
        "cast_ziqi" : "氤氲紫气",
        "perform_feiyin" : "天外飞音",
        "perform_dssh" : "断丝锁魂",
        "perform_mantian" : "青霞漫天",
        "perform_tong" : "姐妹同心",
        "perform_moyin" : "万铃魔音",
        "perform_qinghua" : "盘丝情花阵",
        "perform_tian" : "天上人间",
        "perform_wang" : "天罗地网",
//puti
        "cast_dingshen" : "定身咒",
        "cast_light" : "苍灵箭",
        "cast_thunder" : "五雷咒",
        "perform_sanhuan" : "三环套月",
        "perform_yin" : "阴字诀",
        "perform_tanzhi" : "弹指惊魂",
        "perform_panlong" : "盘龙八棍",
        "perform_pili" : "霹雳三打",
        "perform_qiankun" : "乾坤一棒",
        "perform_santouliubi" : "三头六臂",
        "perform_wu" : "神猴乱舞",
        "exert_jldl" : "借力打力",
//sanxian
        "perform_break" : "五遁绝杀",
        "perform_fen" : "焚心以火",
        "perform_poshi" : "破势刀",
        "perform_cangyun" : "苍茫云海间",
        "perform_shudao" : "蜀道之难，难于上青天",
        "perform_zui" : "醉舞",
        "cast_baigui" : "百鬼夜行",
        "cast_fu" : "符之术",
        "perform_bishou" : "图穷匕现",
        "perform_dunnoname" : "名可名 非常名",
        "perform_dunnotruth" : "道可道 非常道",
        "perform_bolt" : "阴阳光球",
//shushan
        "perform_ninglei" : "凝泪诀",
        "perform_wsry" : "往事如烟",
        "perform_xiangsi" : "相思三剑",
        "perform_fenguang" : "纷光化影",
        "perform_jianqi" : "蜀山剑气",
        "perform_tanzhi" : "弹指相思",
        "perform_taohua" : "桃花飞舞",
        "cast_fu" : "天师符法",
        "cast_jianshen" : "剑神诀",
        "cast_jiushen" : "酒神诀",
        "perform_qjqy" : "絕情絕意",
        "perform_yue" : "冷浸溶溶月",
        "perform_duanshui" : "断水无痕",
        "perform_wanjian" : "万剑诀",
//suburb
        "perform_badao" : "拔刀诀",
        "perform_qijian" : "大雅剑气",
        "perform_polu" : "破颅击",
        "perform_xueying" : "金龙血影击",
        "perform_chiri" : "赤日金芒",
        "perform_chiyan" : "赤炎斩",
        "perform_jinhong" : "大漠金虹",
        "perform_luori" : "落日诀",
        "perform_shipo" : "石破天惊",
        "perform_fengliu" : "忘情诀·风流",
        "perform_wangqing" : "忘情诀·忘情",
        "perform_yunyi" : "忘情诀·云翳",
        "cast_lei" : "雷霆霹雳",
        "cast_leidong" : "雷动九天",
        "perform_xueqi" : "血气惊天",
        "perform_xuezong" : "血踪万里",
//yaomo/kusong
        "perform_back" : "魔王回首",
        "exert_fire" : "三味真火",
        "perform_huohun" : "火魂诀",
        "perform_ji" : "祭枪诀",
        "perform_lihuo" : "离火三重",
        "perform_zhangxinlei" : "掌心雷",
        "cast_niushi" : "召唤牛虱",
        "cast_sanmei" : "三味真火",
        "cast_zhuang" : "撞字咒",
        "perform_buhui" : "至死不悔",
        "perform_chongxiu" : "秀冲青天",
        "perform_fengchan" : "五岳封禅",
        "perform_feicha" : "飞叉诀",
//yaomo/wudidong
        "exert_shuyi" : "鼠疫成灾",
        "exert_zhangqi" : "桃花瘴",
        "perform_diyu" : "无边地狱",
        "perform_pozhan" : "破绽百出",
        "perform_xiao" : "刀剑笑",
        "perform_duoming" : "夺命七剑",
        "perform_yaowu" : "妖雾冲天",
        "perform_zxzx" : "追腥逐血",
        "cast_bite" : "化身咒",
        "perform_wuji" : "魔光日无极",
//yaomo/xueshan
        "perform_chaofeng" : "百鸟朝凤",
        "perform_feijian" : "御剑回飞",
        "perform_fengwu" : "凤舞九天",
        "perform_qijue" : "凤凰七绝",
        "perform_bingxue" : "冰风雪雨",
        "perform_ningxie" : "凝血诀",
        "perform_qianshe" : "千蛇出洞",
        "perform_wind" : "寒冰诀",
        "perform_windstrike" : "风刀波",
        "perform_cuixin" : "摧心掌",
        "cast_jieti" : "天魔解体",
        "cast_juanbi" : "扭转乾坤",
        "cast_tuntian" : "魔兽吞天",
        "exert_ningxie" : "冰谷凝血功",
        "perform_xiaoyao" : "逍遥游",
//zhenyuan
        "perform_fuhu" : "降龙伏虎",
        "perform_poyuan" : "破元心",
        "perform_bxzui" : "八仙醉剑",
        "perform_jianmang" : "三清剑芒",
        "perform_jianzhang" : "掌剑诀",
        "perform_juejian" : "三清绝剑",
        "perform_move" : "星移斗转",
        "perform_sanqing" : "一剑化三清",
        "cast_baxian" : "八仙大阵",
        "cast_qiankun" : "袖里乾坤",
        "cast_qimen" : "奇门遁甲",
        "cast_zhenhuo" : "太乙真火",
        "perform_guiwei" : "五行归位",
        "perform_huichang" : "荡气回肠",
        "perform_zouxiao" : "碧箫传情",
        "perform_damoyange" : "大漠雁歌",
]);

void create ()
{
    set("short", "开来");
    set("long","\n\n\n\n");
    set("no_quit",1);
    set("no_flee",1);
    set("alternative_die",1);
    set("channel_id","挑战任务");
    set("virtual_room",1);
    setup();
}

int is_tiaozhan(){return 1;}

int get_player(object who)
{
    int i;
    object *inv;
    if( !who )
        return 0;
    inv = all_inventory(who);
    for(i=0;i<sizeof(inv);i++)
        if( userp(inv[i]) )
            return 1;
    return 0;
}                

void tell_object(object who,string arg)
{
	arg = HIG"【星月挑战】"+arg+NOR;
	return efun::tell_object(who,arg);
}

void alternative_die (object me)
{
    string *winner_msg,str,log,killmsg,rkmsg;
    mapping KillMsg;
    object npc,ob,*inv;
    int i;
    if( !me )
        return;
 	winner_msg = ({
    	CYN "\n$N"CYN"哈哈大笑，说道：承让了！\n\n" NOR,
    	CYN "\n$N"CYN"双手一拱，笑着说道：承让！\n\n" NOR,
    	CYN "\n$N"CYN"胜了这招，向后跃开三尺，笑道：承让！\n\n" NOR,
    	CYN "\n$n"CYN"脸色微变，说道：佩服，佩服！\n\n" NOR,
    	CYN "\n$n"CYN"向后退了几步，说道：这场比试算我输了，佩服，佩服！\n\n" NOR,
    	CYN "\n$n"CYN"向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n" NOR,
	});        
	npc = me->query_temp("last_damage_from");
    if( npc && npc->is_job() && present(npc,this_object()) )
    {
        killmsg = npc->query_temp("kill_msg");
        if( killmsg )
        {
       		if( !undefinedp(KillMsg2[killmsg]) )
       		{
            	rkmsg = KillMsg2[killmsg];
				str=me->name(1)+"在"+query("short")+"被"+npc->name(1)+HIM"以一招「"HIW+rkmsg+HIM"」打翻在地。"NOR;
                if( userp(me) )  CHANNEL_D->do_channel(this_object(), "rumor",str);
    		}
    	}	
        message_vision(winner_msg[random(sizeof(winner_msg))],npc,me);    	
    }	    
        
    me->remove_all_killer();
    all_inventory()->remove_killer(me);
    if( userp(me) )
    {
        if( time()<me->query("mark/tiaozhan/last_die")+3600          //假死时间没到
         || me->query("combat_exp")<10000
         || me->query("daoxing")<10000 
         || !me->query("obstacle/reward") )
        {
            delete("alternative_die");
            me->set("mark/tiaozhan/last_out",time());
            me->die();
            log = sprintf("%s %s 因假死时间未到|WD不足，而在挑战地图 %s 中真死.\n",ctime(time()), me->query("id"), query("short") );
            log_file("挑战死亡记录",log);               
            set("alternative_die",1);
            return;
        }
        me->set("kee", 100);
        me->set("sen", 100);
        me->set("force",100);
        me->set("mana",100);
        me->clear_condition();
        me->delete_temp("no_move");
        me->set("eff_kee",me->query("max_kee"));
        me->set("eff_sen",me->query("max_sen"));
        me->add("combat_exp",-1000);
        me->add("daoxing",-1000);
		tell_object(me,"你失去了一千武学和道行。\n");    
        me->save();
        if( npc ) npc->powerup(1);
        return;
    }        
//NPC
    if( !me->is_job() )
    {
        message_vision(HIY"\n金光一闪，$N"HIY"顿时化为灰灰。\n\n"NOR,me);    
        destruct(me);
        return;
    }
    ob = me->query_temp("last_damage_from");
    if( !ob || !userp(ob) || !living(ob) || !present(ob,environment(me)) )
    {
        me->powerup(1);
        return;
    }
//MASTER    
	me->reward_ob(ob);
	return;
}

void reset()
{
    int i;
    object *inv;
    if( query("master") && objectp(present(query("master"),this_object())) )
        return;
    tell_room(this_object(),"\n\n一声巨响，天地好似都在震动。。。。\n\n\n");
    inv = all_inventory();
    for(i=0;i<sizeof(inv);i++)
    {
        if( inv[i] && !inv[i]->is_fighting() 
        && !inv[i]->is_job() && !wizardp(inv[i]) )
        {
            message_vision("一阵天旋地转中，$N脚下一滑，不见了踪影！\n\n",inv[i]);
            if( !userp(inv[i]) )
                destruct(inv[i]);
            else    
                MISC_D->random_capture(inv[i],1,1);
        }
    }
    ::reset();
}

void init()
{
	object me = this_player();
	if( get_player(me) )
	{
		me->move("/d/dntg/sky/beitian",1);
		tell_object(me,"你得先将身上的玩家放下。\n");
		return;
	}
}
