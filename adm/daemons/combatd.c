// combatd.c
// #pragma optimize

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
#include "/cmds/std/valid_kill.h"
#include "/cmds/std/valid_move.h"
inherit F_DBASE;

nosave int baoji = 0;

string *guard_msg = ({
    CYN "\n$N"CYN"注视着$n"CYN"的行动，企图寻找机会出手。\n\n" NOR,
    CYN "\n$N"CYN"正盯着$n"CYN"的一举一动，随时准备发动攻势。\n\n" NOR,
    CYN "\n$N"CYN"缓缓地移动脚步，想要找出$n"CYN"的破绽。\n\n" NOR,
    CYN "\n$N"CYN"目不转睛地盯着$n"CYN"的动作，寻找进攻的最佳时机。\n\n" NOR,
    CYN "\n$N"CYN"慢慢地移动着脚步，伺机出手。\n\n" NOR,
});

string *catch_hunt_msg = ({
    HIW "\n$N"HIW"和$n"HIW"仇人相见份外眼红，立刻打了起来！\n\n" NOR,
    HIW "\n$N"HIW"对着$n"HIW"大喝：「可恶，又是你！」\n\n" NOR,
    HIW "\n$N"HIW"和$n"HIW"一碰面，二话不说就打了起来！\n\n" NOR,
    HIW "\n$N"HIW"一眼瞥见$n"HIW"，「哼」的一声冲了过来！\n\n" NOR,
    HIW "\n$N"HIW"一见到$n"HIW"，愣了一愣，大叫：「我宰了你！」\n\n" NOR,
    HIW "\n$N"HIW"喝道：「$n"HIW"，我们的帐还没算完，看招！」\n\n" NOR,
    HIW "\n$N"HIW"喝道：「$n"HIW"，看招！」\n\n" NOR,});

string *winner_msg = ({
    CYN "\n$N"CYN"哈哈大笑，说道：承让了！\n\n" NOR,
    CYN "\n$N"CYN"双手一拱，笑着说道：承让！\n\n" NOR,
    CYN "\n$N"CYN"胜了这招，向后跃开三尺，笑道：承让！\n\n" NOR,
    CYN "\n$n"CYN"脸色微变，说道：佩服，佩服！\n\n" NOR,
    CYN "\n$n"CYN"向后退了几步，说道：这场比试算我输了，佩服，佩服！\n\n" NOR,
    CYN "\n$n"CYN"向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n" NOR,
});

mapping limb_damage = ([
// 人类身体部位
    "头部" : 100,    "颈部" : 90,    "胸口" : 90,
    "后心" : 80,     "左肩" : 50,    "右肩" : 55,
    "左臂" : 40,     "右臂" : 45,    "左手" : 20,
    "右手" : 30,     "腰间" : 60,    "小腹" : 70,
    "左腿" : 40,     "右腿" : 50,    "左脚" : 35,
    "右脚" : 40,
//  动物身体部位
    "身体" : 80,     "前脚" : 40,    "后脚" : 50,
    "腿部" : 40,     "尾巴" : 10,    "翅膀" : 50,
    "爪子" : 40,
]);

string *danger_limbs = ({
    	"头部", "颈部", "胸口", "后心","小腹",
});

string *head_damage_me_msg = ({
    HIR"$n"HIR"觉得头有一点发晕。\n"NOR,
    HIB "$n"HIB"觉得一阵晕眩，身体晃了一下。\n"NOR,
    BLU "$n"BLU"只得眼冒金星，浑身发飘。\n" NOR,
});

string *body_damage_me_msg = ({
    HIY "$n"HIY"只觉$l隐隐作痛，感觉收到了一定的内伤。\n" NOR
    HIR "$n"HIR"只觉$l生疼，内息稍稍有些混乱。\n" NOR,
    RED "$n"RED"只觉得$l处剧痛，受到了严重的内伤。\n" NOR,
    RED "$n"RED"只觉得$l处剧痛，受到了严重的内伤。\n" NOR,
});

mapping damage_msgs = ([
    "擦伤"  : ({
        "结果只在$p$l擦出一条淤青的痕迹。\n",
        "结果$p$l给擦出一条细长的划痕。\n",
        "结果「嗤」的一声，$p$l现出一抹长长的伤痕，沁出点点的鲜血！\n",
        "结果鲜血从$p$l新增的擦痕处「哗」的流溅而出！\n",
        "结果只听$n一声闷哼，捂住一条深长伤口，鲜血止不住的从指缝流出！\n",
        "结果只见$n$l皮肉翻转，血肉模糊，一条长长的伤口处隐隐可见皑皑白骨！\n",
        }),
    "抓伤"  : ({
        "结果只在$p$l抓出一条红肿的血迹。\n",
        "结果$p$l给抓出一条细长的血痕。\n",
        "结果$p$l的衣襟给抓得片片飞散，隐约可见悚然的血印！\n",
        "结果$p$l处的衣襟给抓出一道长长的口子，鲜血止不住的向外直淌！\n",
        "结果从$n$l破碎的衣襟可见一条又长又深的伤口向外淌着鲜血！\n",
        "结果只见$n闷哼一声，连连后退，$l衣襟破碎，血肉模糊，！\n",
        }),
    "割伤"  : ({
        "结果只是轻轻地划破$p的皮肉。\n",
        "结果在$p$l划出一道细长的血痕。\n",
        "结果「嗤」地一声划出一道伤口！\n",
        "结果「嗤」地一声划出一道血淋淋的伤口！\n",
        "结果「嗤」地一声划出一道又长又深的伤口，溅得$N满脸鲜血！\n",
        "结果只听见$n一声惨嚎，$p的$l被划出一道深及见骨的可怕伤口！\n",
        }),
    "砍伤"  : ({
        "结果$w从$n$l旁带过，劲风吹得$p的衣襟「嗍嗍」直响。\n",
        "结果在$n$l砍出一道细长的血痕。\n",
        "结果「噗嗤」一声劈出一道血淋淋的伤口！\n",
        "结果只听「噗」地一声，$n的$l被劈得血如泉涌，痛得$p咬牙切齿！\n",
        "结果「噗」地一声砍出一道又长又深的伤口，溅得$N满脸鲜血！\n",
        "结果只听见$n一声惨嚎，$p的$l被劈开一道深及见骨的可怕伤口！\n",
        }),
    "劈伤"  : ({
        "结果只是在$n的皮肉上碰了碰，跟蚊子叮差不多。\n",
        "结果在$n$l砍出一道细长的血痕。\n",
        "结果「噗嗤」一声劈出一道血淋淋的伤口！\n",
        "结果只听「噗」地一声，$n的$l被劈得血如泉涌，痛得$p咬牙切齿！\n",
        "结果「噗」地一声砍出一道又长又深的伤口，溅得$N满脸鲜血！\n",
        "结果只听见$n一声惨嚎，$p的$l被劈开一道深及见骨的可怕伤口！\n",
        }),
    "枪伤"  : ({
        "结果$w「噗」的一声，将$p$l处的皮肉挑了小口。\n",
        "结果「嗤」的一声，血花飞溅中$p$l已经多出一个醒目的创口。\n",
        "结果$w「噗」地一声刺入了$n$l寸许！\n",
        "结果「噗」地一声$w扎进$n的$l，使$p不由自主地退了步！\n",
        "结果「噗嗤」地一声，$w已在$p$l扎出一个血肉模糊的血窟窿！\n",
        "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！\n",
        }),
    "戳伤"  : ({
        "结果$w「噗」的一声，将$p$l处的皮肉挑了小口。\n",
        "结果「嗤」的一声，血花飞溅中$p$l已经多出一个醒目的创口。\n",
        "结果$w「噗」地一声刺入了$n$l寸许！\n",
        "结果「噗」地一声$w扎进$n的$l，使$p不由自主地退了步！\n",
        "结果「噗嗤」地一声，$w已在$p$l扎出一个血肉模糊的血窟窿！\n",
        "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！\n",
        }),
    "刺伤"  : ({
        "结果只是轻轻地刺破$p的皮肉。\n",
        "结果在$p$l刺出一个创口。\n",
        "结果「噗」地一声刺入了$n$l寸许！\n",
        "结果「噗」地一声刺进$n的$l，使$p不由自主地退了步！\n",
        "结果「噗嗤」地一声，$w已在$p$l刺出一个血肉模糊的血窟窿！\n",
        "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！\n",
        }),
    "筑伤"  : ({
        "结果只是轻轻地一触，在$n的皮肤上留下一点白痕。\n",
        "结果在$p的$l留下几道血痕。\n",
        "结果一下子筑中，$n立刻血流如注！\n",
        "结果「哧」地一声，$n顿时鲜血飞溅！\n",
        "结果这一下「哧」地一声，$n被筑得浑身是血！\n",
        "结果「哧」重重地砸中，$n被筑得千疮白孔，血肉四处横飞！\n",
        }),
    "掌伤"  : ({
        "结果拍个正着，可惜劲道只比拍苍蝇稍微重了点。\n",
        "结果「啪」的一声，$p的$l立刻瘀青了一块。\n",
        "结果「砰」地一声，$n退了两步，面色变得十分难看！\n",
        "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n",
        "结果一掌正拍在$p$l，$n连退数步，面色刹时变得苍白！\n",
        "结果只听见「砰」地一声巨响，$n口中鲜血喷出，整个人横飞了出去！\n",
        }),
    "拳伤"  : ({
        "结果捣了正着，可惜力道只比拍苍蝇稍微重了点。\n",
        "结果打了个正着，$n的$l登时肿了一块老高！\n",
        "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n",
        "结果这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n",
        "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n",
        "结果只听见「砰」地一声巨响，$n像一捆稻草般飞了出去！\n",
        }),
    "瘀伤"  : ({
        "结果只是轻轻地碰到，比拍苍蝇稍微重了点。\n",
        "结果在$p的$l造成一处瘀青。\n",
        "结果一击命中，$n的$l登时肿了一块老高！\n",
        "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n",
        "结果这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n",
        "结果只听见「砰」地一声巨响，$n像一捆稻草般飞了出去！\n",
        }),
    "撞伤"  : ({
        "结果在$p的$l撞出一个小臌包。\n",
        "结果撞个正着，$n的$l登时肿了一块老高！\n",
        "结果「砰」地一声，$n给撞得连腰都弯了！\n",
        "结果这一下「轰」地一声撞得$n眼冒金星，差一点摔倒！\n",
        "结果重重地撞中，$n眼前一黑，「哇」地一声吐出一口鲜血！\n",
        "结果只听见「轰」地一声巨响，$n像一捆稻草般飞了出去！\n",
        }),
    "砸伤"  : ({
        "结果只是轻轻地碰到，等于给$n搔了一下痒。\n",
        "结果砸个正着，$n的$l登时肿了一块老高！\n",
        "结果砸个正着，$n闷哼一声显然吃了不小的亏！\n",
        "结果「砰」地一声，$n疼得连腰都弯了！\n",
        "结果这一下「轰」地一声砸得$n眼冒金星，差一点摔倒！\n",
        "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！\n",
        }),
    "震伤"  : ({
        "结果在$n身上一触即逝，等于给$n搔了一下痒。\n",
        "结果$n晃了一晃，吃了点小亏。\n",
        "结果$n气息一窒，显然有点呼吸不畅！\n",
        "结果$n体内一阵剧痛，看起来内伤不轻！\n",
        "结果「嗡」地一声$n只觉得眼前一黑，双耳轰鸣不止！\n",
        "结果只听见「嗡」地一声巨响，$n「哇」地一声吐出一口鲜血，五脏六腑都错了位！\n",
        }),
    "内伤"  : ({
        "结果在$n身上一触即逝，等于给$n搔了一下痒。\n",
        "结果$n晃了一晃，吃了点小亏。\n",
        "结果$n气息一窒，显然有点呼吸不畅！\n",
        "结果$n体内一阵剧痛，看起来内伤不轻！\n",
        "结果「嗡」地一声$n只觉得眼前一黑，双耳轰鸣不止！\n",
        "结果只听见「嗡」地一声巨响，$n「哇」地一声吐出一口鲜血，五脏六腑都错了位！\n",
        }),
    "鞭伤"  : ({
        "结果$w只是在$n的皮肉上碰了碰，跟蚊子叮差不多。\n",
        "结果在$n$l抽出一道轻微的紫痕。\n",
        "结果「啪」地一声在$n$l抽出一道长长的血痕！\n",
        "结果只听「啪」地一声，$n的$l被抽得皮开肉绽，痛得$p咬牙切齿！\n",
        "结果「啪」地一声爆响！这一下好厉害，只抽得$n皮开肉绽，血花飞溅！\n",
        "结果只听见$n一声惨嚎，$w重重地抽上了$p的$l，$n顿时血肉横飞，十命断了九条！\n",
        }),
    "抽伤"  : ({
        "结果$w只是在$n的皮肉上碰了碰，跟蚊子叮差不多。\n",
        "结果在$n$l抽出一道轻微的紫痕。\n",
        "结果「啪」地一声在$n$l抽出一道长长的血痕！\n",
        "结果只听「啪」地一声，$n的$l被抽得皮开肉绽，痛得$p咬牙切齿！\n",
        "结果「啪」地一声爆响！这一下好厉害，只抽得$n皮开肉绽，血花飞溅！\n",
        "结果只听见$n一声惨嚎，$w重重地抽上了$p的$l，$n顿时血肉横飞，十命断了九条！\n",
        }),
    "反震伤" : ({
        "结果$N受到$n的内力反震，闷哼一声。\n",
        "结果$N被$n的反震得站立不稳，摇摇晃晃。\n",
        "结果$N被$n以内力反震，「嘿」地一声退了两步。\n",
        "结果$N被$n的震得反弹回来的力量震得半身发麻。\n",
        "结果$N被$n的内力反震，胸口有如受到一记重击，连退了五六步！\n",
        "结果$N被$n内力反震，眼前一黑，狂吐鲜血，身子象断了线的风筝向後飞去！！\n",
        }),
    "点穴"  : ({
        "结果$n痛哼一声，在$p的$l造成一处淤青。\n",
        "结果一击命中，$N点中了$n$l上的穴道，$n只觉一阵麻木！\n",
        "结果$n闷哼了一声，脸上一阵青一阵白，登时觉得$l麻木！\n",
        "结果$n脸色一下变得惨白，被$N点中$l的穴道,一阵疼痛遍布整个$l！\n",
        "结果$n一声大叫，$l的穴道被点中,疼痛直入心肺！\n",
        "结果只听见$n一声惨叫，一阵剧痛夹杂着麻痒游遍全身，跟着直挺挺的倒了下去！\n",
        }),
    "法术"  : ({
        "结果$n痛哼一声，脸色有少许发白。\n",
        "结果$n只觉心神一阵震荡，脸色顿时变得有些青白！\n",
        "结果$n闷哼了一声，脸上一阵青一阵白，精神好似有些萎靡！\n",
        "结果$n脸色一下变得惨白，$l上的疼痛直达元神深处！\n",
        "结果$n一声惨叫，脸色一片惨白，三魂七魄好似要突体而去！\n",
        "结果只听见$n一声惨叫，脸色全无人样，三魂七魄好似散了一般，整个人顿时浑浑噩噩！\n",
        }),
    "其他"  : ({
        "结果造成轻微的伤势！\n",
        "结果造成一处严重伤势！\n",
        "结果造成颇为严重的伤势！\n",
        "结果造成相当严重的伤势！\n",
        "结果造成极其严重的伤势！\n",
        "结果造成非常可怕的严重伤势！\n",
        }),
]);

varargs string chinese_daoxing(int gain,int flag)
{
	return CHINESE_D->chinese_daoxing(gain,flag);
}

string eff_status_msg(int ratio)
{
    if( ratio==100 ) return HIG "看起来气血充盈，并没有受伤。"NOR;
    if( ratio > 95 ) return HIG "似乎受了点轻伤，不过光从外表看不大出来。"NOR;
    if( ratio > 90 ) return HIY "看起来可能受了点轻伤。"NOR;
    if( ratio > 80 ) return HIY "受了几处伤，不过似乎并不碍事。"NOR;
    if( ratio > 60 ) return HIY "受伤不轻，看起来状况并不太好。"NOR;
    if( ratio > 40 ) return HIR "气息粗重，动作开始散乱，看来所受的伤着实不轻。"NOR;
    if( ratio > 30 ) return HIR "已经伤痕累累，正在勉力支撑着不倒下去。"NOR;
    if( ratio > 20 ) return HIR "受了相当重的伤，只怕会有生命危险。"NOR;
    if( ratio > 10 ) return RED "伤重之下已经难以支撑，眼看就要倒在地上。"NOR;
    if( ratio > 5  ) return RED "受伤过重，已经奄奄一息，命在旦夕了。"NOR;
    return RED "受伤过重，已经有如风中残烛，随时都可能断气。"NOR;
}

string status_msg(int ratio)
{
    if( ratio==100 ) return HIG "看起来充满活力，一点也不累。"NOR;
    if( ratio > 95 ) return HIG "似乎有些疲惫，但是仍然十分有活力。"NOR;
    if( ratio > 90 ) return HIY "看起来可能有些累了。"NOR;
    if( ratio > 80 ) return HIY "动作似乎开始有点不太灵光，但是仍然有条不紊。"NOR;
    if( ratio > 60 ) return HIY "气喘嘘嘘，看起来状况并不太好。"NOR;
    if( ratio > 40 ) return HIR "似乎非常疲惫，看来需要好好休息了。"NOR;
    if( ratio > 30 ) return HIR "已经一副头重脚轻的模样，正在勉力支撑着不倒下去。"NOR;
    if( ratio > 20 ) return HIR "看起来已经力不从心,马上要支持不住了。"NOR;
    if( ratio > 10 ) return RED "摇头晃脑、歪歪斜斜地站都站不稳，眼看就要倒在地上。"NOR;
    return RED "已经陷入半昏迷状态，随时都可能摔倒晕去。"NOR;
}

string sen_status_msg(int ratio)
{
    if( ratio==100 ) return HIG "看起来头脑清醒，一点也不迷糊。"NOR;
    if( ratio > 90 ) return HIG "拍了拍自己的脑袋，似乎有点不太得劲。"NOR;
    if( ratio > 80 ) return HIY "看起来有些迷糊了。"NOR;
    if( ratio > 60 ) return HIY "的确有点迷糊了，但还辨得出东西南北。"NOR;
    if( ratio > 40 ) return HIR "两眼发直，口角流涎，神智开始混乱。"NOR;
    if( ratio > 20 ) return HIR "迷迷糊糊，摇摇晃晃，已经辨不出东西南北了。"NOR;
    if( ratio > 10 ) return RED "神智已经处在极度混乱中,再也支持不住了。"NOR;
    return RED "心智已经完全迷失，随时都有可能背过气去。"NOR;
}

varargs void report_status(object ob, int effective)
{
    	string str;
    	if( stringp(str=ob->query_report_status(effective)) )
		message_vision( "( $N"+str+" )\n",ob);
    	else if( effective )
        	message_vision( "( $N" + eff_status_msg((int)ob->query("eff_kee") * 100 /(1+(int)ob->query_maxkee()))+ " )\n", ob);
    	else    message_vision( "( $N" + status_msg((int)ob->query("kee") * 100/(1+(int)ob->query_maxkee()) ) + " )\n", ob);
}

varargs void report_sen_status(object ob, int effective)
{
    	string str;
    	if( stringp(str = ob->query_report_sen_status()) )
        	message_vision( "( $N"+str+" )\n",ob);
    	else    message_vision( "( $N" + sen_status_msg((int)ob->query("sen") * 100 /(1+(int)ob->query_maxsen()) ) + " )\n", ob);
}

string damage_msg(int damage, string type)
{
    	if( damage == 0 )
        	return "结果没有造成任何伤害。\n";
    	if( member_array(type,keys(damage_msgs))==-1 )
        	type = "其他";
    	if( damage<10 )
	        return damage_msgs[type][0];
    	else if( damage<20 )
        	return damage_msgs[type][1];
    	else if( damage<40 )
        	return damage_msgs[type][2];
    	else if( damage<60 )
        	return damage_msgs[type][3];
    	else if( damage<80 )
        	return damage_msgs[type][4];
    	else    return damage_msgs[type][5];
}

mapping KillMsg = ([
    "slash"  : "斩",     "slice"  : "砍",     "chop"   : "劈",     "hack"   : "劈",
    "thruse" : "刺",     "pierce" : "刺",     "wave"   : "鞭",     "whip"   : "抽",
    "impale" : "戳",     "rake"   : "筑",     "bash"   : "砸",     "crush"  : "砸",
    "slam"   : "挫",     "throw"  : "射",     "shoot"  : "射",
]);

mapping KillMsg2 = ([
	"月宫" : ([
		"perform_flower": "天女散花",          "perform_tian": "漫天飞雪",
		"perform_dance": "清歌妙舞",           "perform_yixiao": "倾城一笑",
		"perform_diezhang": "叠掌",            "perform_huifeng": "回风舞柳",
		"perform_changhen": "长恨天歌",        "perform_duanfa": "断发忘情",
		"perform_qingmang": "青芒三式",        "cast_shiyue": "蚀月咒",
		"perform_sanshou": "三无三不手",       "cast_arrow": "落日神箭",
		"cast_huimeng": "回梦咒",              "perform_qin": "倾城倾国",
		"cast_mihun": "迷魂咒",
	]),
	"南海普陀山" : ([
		"cast_bighammer": "大力降魔杵",        "cast_jingang": "金刚咒",
		"cast_jinguzhou": "紧箍咒",            "perform_cibei": "慈悲刀诀",
		"perform_sheshen": "舍身喂鹰",         "perform_lian": "慈悲连环",
		"perform_lingxi": "灵犀一指",          "perform_wanfo": "万佛朝宗",
		"perform_wuzhi": "五指山",             "perform_pudu": "慈光普渡",
		"perform_chaodu": "超生渡化",          "perform_sandu": "佛门三渡",
		"perform_fire": "八方火焱",
	]),
	"阎罗地府" : ([
		"cast_fire": "黄泉鬼火",               "cast_gouhun": "勾魂咒",
		"perform_zhua": "无常爪",              "perform_ku": "历鬼三哭",
		"perform_three": "人·鬼·神",           "perform_qmly": "青面獠牙",
		"perform_suoming": "冤魂索命",         "perform_xingyun": "鬼火腥云",
		"perform_biluo": "碧落黄泉",           "perform_ldlh": "六道轮回",
		"exert_sheqi": "摄气诀",               "perform_yanluo": "歌舞阎罗",
		"perform_duoming": "追魂夺命",         "perform_dengku": "油尽灯枯",
	]),
	"方寸山三星洞" : ([
		"cast_light": "苍灵箭",                "cast_thunder": "五雷咒",
		"perform_wu": "神猴狂舞",              "perform_yin": "阴字诀",
		"perform_yang": "阳字诀",              "perform_shuangyu": "双鱼诀",
		"perform_jinghun": "惊魂一指",         "perform_qiankun": "乾坤一棒",
		"perform_pili": "霹雳流星",            "perform_leiting": "雷霆一击",
		"perform_panlong": "盘龙八式",         "exert_jldl": "借力打力",
	]),
	"大雪山" : ([
		"perform_feijian": "飞鸟投林",         "perform_chaofeng": "百鸟朝风",
		"perform_fengwu": "凤舞九天",          "perform_qijue": "凤凰七绝",
		"exert_ningxie": "凝血大法",           "perform_ningxie": "冰谷凝血",
		"perform_daobo": "雪风刀波",           "perform_bingxue": "冰风雪雨",
		"perform_qianshe": "千蛇出洞",         "perform_cuixin": "摧心掌",
		"perform_suoxin": "冰爪锁心",          "cast_juanbi": "扭转乾坤",
		"cast_tuntian": "魔兽吞天",            "cast_jieti": "天魔解体",
	]),
	"五庄观" : ([
		"perform_fuhu": "降龙伏虎",            "perform_luan": "乱披风",
		"perform_poyuan": "破元一击",          "perform_jin": "金骨炼真",
		"perform_jianzhang": "剑中出掌",       "perform_jianmang": "三清剑芒",
		"perform_juejian": "三清绝剑",         "perform_sanqing": "一剑三清",
		"perform_move": "斗转星移",            "perform_bxzui": "八仙醉剑",
		"cast_zhenhuo": "太乙真火",            "perform_wuxing": "相生相克",
		"perform_huichang": "荡气回肠",        "perform_xiao": "碧箫传情",
		"perform_yange": "大漠雁歌",           "perform_bafang": "八方风雨",
	]),
	"东海龙宫" : ([
		"cast_freez": "雪舞风灵",              "cast_water": "双龙水柱",
		"perform_fengbo": "无尽风波",          "perform_bibo": "碧波浪涌",
		"perform_dhwl": "大海无量",            "perform_break": "混元一破",
		"perform_fan": "翻江倒海",             "exert_roar": "碧海龙吟",
		"perform_leidong": "雷动九天",         "perform_sheshen": "舍身技",
		"perform_shenglong": "升龙技",         "perform_yansha": "黑龙炎杀",
	]),
	"将军府" : ([
		"cast_light": "神霄电法符",            "cast_poison": "五瘟符",
		"cast_rain": "神霄雨法符",             "cast_thunder": "神霄雷法符",
		"perform_jian": "枪里加锏",            "perform_bugong": "不攻有悔",
		"perform_huima": "回马枪",             "perform_juanlian": "珍珠倒卷帘",
		"perform_meihua": "梅花六出",          "perform_jueming": "绝命九枪",
		"perform_chong": "冲字诀",             "perform_zhi": "窒气诀",
		"perform_hengsao": "横扫千军",         "perform_pofu": "破釜沉舟",
		"perform_lei": "雷殛怒火",             "perform_jue": "万刃神兵诀",
		"perform_feijian": "撒手锏",           "perform_andu": "暗渡陈仓",
		"perform_jingtian": "惊天吼地",        "perform_suomeng": "锁梦缠魂",
		"perform_kai": "开天斩",               "perform_pidi": "辟地斩",
		"perform_sanban": "无敌三板斧",        "perform_potian": "破天斩",
	]),
	"火云洞" : ([
		"perform_back": "魔王回首",            "perform_wujin": "妖云无尽",
		"exert_fire": "离体真火",              "perform_ji": "火灵祭枪",
		"perform_lihuo": "离火三重",           "perform_lei": "掌心雷",
		"perform_yin": "五岳镇印",             "perform_yao": "摇头摆尾",
		"cast_tashan": "踏山裂石",             "cast_zhuang": "横冲直撞",
		"cast_sanmei": "三味真火",             "perform_buhui": "不见南山誓不回",
		"perform_chongxiu": "秀冲青天",        "perform_fengchan": "五岳封禅",
	]),
	"陷空山无底洞" : ([
		"exert_shuyi": "鼠疫成灾",             "perform_pozhan": "破绽百出",
		"exert_diyu": "无边地狱",              "perform_xiao": "刀剑啸",
		"perform_shendao": "祭血神刀",         "perform_yaowu": "妖雾冲天",
		"perform_zxzx": "追腥逐血",            "cast_duoming": "夺命七剑",
		"cast_zhangqi": "桃花瘴气",            "perform_wuji": "魔光日无极",
	]),
	"蜀山派" : ([
		"perform_chuanyun": "穿云裂石",        "perform_fuyu": "覆雨翻云",
		"perform_yunqi": "云起龙骧",           "perform_yunchu": "云出无心",
		"perform_biao": "铜钱镖",              "perform_qiankun": "乾坤一掷",
		"perform_yujian": "御剑术",            "perform_qijue": "七诀剑气",
		"perform_zhan": "斩龙诀",              "perform_wanjian": "万剑诀",
		"perform_jianshen": "剑神",            "cast_fu": "天师符法",
		"cast_ding": "束身定",                 "cast_feng": "禁咒封",
		"cast_zhan": "魔炎闪空斩",
	]),
	"盘丝洞" : ([
		"perform_hongyan": "红颜白发",         "perform_huadie": "化蝶",
		"perform_haotan": "痴情八叹",          "perform_juehu": "九阴绝户手",
		"cast_ziqi": "氤氲紫气",               "cast_wuzhi": "佛祖五指",
		"perform_mantian": "青霞漫天",         "perform_tong": "姐妹同心",
		"perform_dssh": "断丝锁魂",            "perform_feiyin": "天外飞音",
		"perform_moyin": "万铃魔音",           "perform_tian": "天上人间",
		"perform_wang": "天罗地网",            "perform_qinghua": "盘丝情花阵",
	]),
	"百花谷" : ([
		"perform_jingshen": "惊神一击",        "perform_siji": "四季飞花",
		"cast_flower": "百花飞舞",             "exert_feng": "寒玉灵风",
		"perform_jingshen": "惊神一击",        "perform_changhong": "长虹经天",
		"perform_wunian": "无念无忧",          "perform_zizai": "自在逍遥",
		"perform_liaorao": "百花缭绕",         "perform_yumei": "雨激梅花半瓣香",
		"perform_qijian": "纵横七剑",          "perform_zongheng": "纵横四海",
		"perform_heng": "横剑",                "perform_zong": "纵剑",
	]),
	"其他" : ([
		"perform_break" : "五遁绝杀",          "perform_fen" : "焚心以火",
		"perform_poshi" : "破势刀",            "perform_cangyun" : "苍茫云海间",
        	"perform_shudao" : "蜀道之难，难于上青天",
        	"perform_zui" : "醉舞",                "cast_baigui" : "百鬼夜行",
        	"cast_fu" : "符之术",                  "perform_bishou" : "图穷匕现",
        	"perform_dunnoname" : "名可名 非常名", "perform_dunnotruth" : "道可道 非常道",
        	"perform_bolt" : "阴阳光球",           "perform_badao" : "拔刀诀",
        	"perform_polu" : "破颅击",             "perform_xueying" : "金龙血影击",
        	"perform_chiri" : "赤日金芒",          "perform_chiyan" : "赤炎斩",
        	"perform_jinhong" : "大漠金虹",        "perform_luori" : "落日诀",
        	"perform_shipo" : "石破天惊",          "perform_fengliu" : "忘情诀·风流",
        	"perform_wangqing" : "忘情诀·忘情",    "perform_yunyi" : "忘情诀·云翳",
        	"cast_lei" : "雷霆霹雳",               "cast_leidong" : "雷动九天",
        	"perform_xueqi" : "血气惊天",          "perform_xuezong" : "血踪万里",
        	//五虎断魂刀
        	"perform_qihu" : "骑虎难下",           "perform_pushi" : "饿虎扑食",
        	"perform_pingying" : "虎落平阳",       "perform_huwei" : "狐假虎威",
        	"perform_cheng" : "三人成虎",
	]),
]);

int victim_lose(object killer,object victim,string killerid);
void victim_penalty(object victim);
int nk_gain(object killer, object victim);

void create()
{
	seteuid(getuid());
    	set("name", "战斗精灵");
    	set("id", "combatd");
}

int check_level(object me,object target)
{
	int ap,dp,b1,s1,g1,b2,s2,g2;
	if( !me || !target )
		return 0;
	ap = me->query_level();
	dp = target->query_level();
	if( ap<40 && dp<40 )
		return 0;
	else if( ap<40 && dp>=40 )
		return -1;
	else if( ap>=40 && dp<40 )
		return 1;
	else if( ap>=190 && dp>=190 )
		return 0;
	b1 = ap/100;
	ap = ap-b1*100;
	s1 = ap/10;
	g1 = ap-s1*10;

	b2 = dp/100;
	dp = dp-b2*100;
	s2 = dp/10;
	g2 = dp-s2*10;

	if( b1>b2 )
		return 1;
	else if( b2>b1 )
		return -1;
	else
	{
		if( s1>s2 )
			return 1;
		else if( s1<s2 )
			return -1;
		else	return 0;
	}
}

//门派相克，1为克制 -1为被克制
int family_restrain(object me,object victim){return FAMILY_D->family_restrain(me,victim);}

//伤害计算
varargs int valid_damage(object me,object victim,string skill,mixed attack_type)
{
	int pp,damage;
	object weapon;
	if( !me || !victim )
		return 0;
	if( !attack_type )
		attack_type = TYPE_COMBAT;
	switch(attack_type)
	{
		case TYPE_CAST :
			damage = me->query_spells_damage();
			damage = damage*9/10+random(damage/10);
			damage = damage*me->query_spi()/60;
			damage+= (me->query_skill(skill)-victim->query_skill("spells"))/49;
			damage-= me->query_spells_damage()*victim->query_spells_def()/(victim->query_spells_def()+victim->query_level()*50+360);
			damage+= me->query("mana_factor")/10+random(me->query("mana_factor")/10);
			if( family_restrain(me,victim)==1 )
				damage = damage*3/2;
			else if( family_restrain(me,victim)==-1 )
				damage = damage*2/3;
			if( damage<1 )
				damage = 1;
			break;
		default:
			damage = me->query_combat_damage();
			damage = damage*9/10+random(damage/10);
			damage = damage*me->query_str()/80;
			damage+= (me->query_skill(skill)-(victim->query_skill("parry")+victim->query("dodge"))/2)/36;
			damage-= me->query_combat_damage()*victim->query_combat_def()/(victim->query_combat_def()+victim->query_level()*50+360);
			damage+= me->query("force_factor")/10+random(me->query("force_factor")/10);
			if( family_restrain(me,victim)==1 )
				damage = damage*11/10;
			else if( family_restrain(me,victim)==-1 )
				damage = damage*9/10;
			if( damage<1 )
				damage = 1;
			break;
	}
	//神通剑术	剑法类招式伤害+5%
	if( attack_type && ( attack_type==TYPE_COMBAT || attack_type==TYPE_PERFORM )
	 && objectp(weapon=me->query_temp("weapon"))
	 && weapon->query("skill_type")=="sword"
	 && me->query_skill("jianshu",2)>100 )
	{
		pp = (me->query_skill("jianshu",1)-100)/210+5;
		damage = damage*(100+pp)/100;
	}
	//神通招云	剑法类招式伤害+5%
	if( attack_type && ( attack_type==TYPE_COMBAT || attack_type==TYPE_PERFORM )
	 && objectp(weapon=me->query_temp("weapon"))
	 && weapon->query("skill_type")=="blade"
	 && me->query_skill("zhaoyun",2)>100 )
	{
		pp = (me->query_skill("zhaoyun",1)-100)/200+5;
		damage = damage*(100+pp)/100;
	}
	//神通断流	unarmed类招式伤害+5%
	if( attack_type && ( attack_type==TYPE_COMBAT || attack_type==TYPE_PERFORM )
	 && objectp(weapon=me->query_temp("weapon"))
	 && weapon->query("skill_type")=="unarmed"
	 && me->query_skill("duanliu",2)>100 )
	{
		pp = (me->query_skill("duanliu",1)-100)/220+5;
		damage = damage*(100+pp)/100;
	}
	//神通萌头	鞭类招式伤害+5%
	if( attack_type && ( attack_type==TYPE_COMBAT || attack_type==TYPE_PERFORM )
	 && objectp(weapon=me->query_temp("weapon"))
	 && weapon->query("skill_type")=="whip"
	 && me->query_skill("mengtou",2)>100 )
	{
		pp = (me->query_skill("mengtou",1)-100)/200+5;
		damage = damage*(100+pp)/100;
	}
	//吐焰	spear类招式伤害+5%
	if( attack_type && ( attack_type==TYPE_COMBAT || attack_type==TYPE_PERFORM )
	 && objectp(weapon=me->query_temp("weapon"))
	 && weapon->query("skill_type")=="spear"
	 && me->query_skill("tuyan",2)>100 )
	{
		pp = (me->query_skill("tuyan",1)-100)/200+5;
		damage = damage*(100+pp)/100;
	}
	//大力	stick类招式伤害+5%
	if( attack_type && ( attack_type==TYPE_COMBAT || attack_type==TYPE_PERFORM )
	 && objectp(weapon=me->query_temp("weapon"))
	 && weapon->query("skill_type")=="stick"
	 && me->query_skill("dali",2)>100 )
	{
		pp = (me->query_skill("dali",1)-100)/200+5;
		damage = damage*(100+pp)/100;
	}
	if( me->query("env/tests") )
		tell_object(me,sprintf(WHT"valid_damage="HIR"%d"NOR"\n",damage));
	return damage;
}

//反弹描述
string re_damage_msg(object who)
{
	string *str,fam = who->query("family/family_name");

	if( stringp(who->query_temp("combat/re_damage_msg")) )
		return (string)who->query_temp("combat/re_damage_msg");
	if( !fam )
	{
		str = ({
			CYN"$n"CYN"虽被击中，却也临危不惧，反团身而上，乘机反攻了一击。\n",
			CYN"$n"CYN"对伤口置若罔闻，乘$N"CYN"得意之际，反攻了一击。\n",
			CYN"$n"CYN"乘$N"CYN"得意之际，团身而上，发起反攻，结果堪堪打中了$P。\n",
		});
		return str[random(sizeof(str))];
	}
	else
	{
		str = ({
			CYN"将伤势部分转嫁于$N"CYN"之身。\n"NOR,
			CYN"将$N"CYN"的攻击反弹了部分回去。\n"NOR,
			CYN"乘机反攻了一击。\n"NOR,
		});

		switch(fam)
		{
			case "方寸山三星洞"  :
				return CYN"$n"CYN"背后隐现菩提异象，"+str[random(sizeof(str))];
			case "蜀山派" :
				return CYN"$n"CYN"背后隐现剑戈之气，"+str[random(sizeof(str))];
				break;
			case "南海普陀山" :
				return CYN"$n"CYN"背后隐现须弥佛国，"+str[random(sizeof(str))];
			case "五庄观" :
				return CYN"$n"CYN"背后隐现地书异象，"+str[random(sizeof(str))];
			case "阎罗地府" :
				return CYN"$n"CYN"背后隐现地狱黄泉，"+str[random(sizeof(str))];
			case "月宫" :
				return CYN"$n"CYN"背后隐现一轮圆月，"+str[random(sizeof(str))];
			case "东海龙宫" :
				return CYN"$n"CYN"浑身隐现层层龙鳞，"+str[random(sizeof(str))];
			case "百花谷" :
				return CYN"$n"CYN"周身百花缭绕，"+str[random(sizeof(str))];
			case "大雪山" :
				return CYN"$n"CYN"背后隐现荒古魔神，"+str[random(sizeof(str))];
			case "陷空山无底洞" :
				return CYN"$n"CYN"背后隐现洪荒妖王，"+str[random(sizeof(str))];
			case "盘丝洞" :
				return CYN"$n"CYN"周身隐隐佛火缠绕，"+str[random(sizeof(str))];
			case "将军府" :
				return CYN"$n"CYN"杀伐之气冲天，"+str[random(sizeof(str))];
			case "火云洞" :
				return CYN"$n"CYN"浑身腾起片片妖火，"+str[random(sizeof(str))];
			default :
				str = ({
					CYN"$n"CYN"虽被击中，却也临危不惧，反团身而上，乘机反攻了一击。\n",
					CYN"$n"CYN"对伤口置若罔闻，乘$N"CYN"得意之际，反攻了一击。\n",
					CYN"$n"CYN"乘$N"CYN"得意之际，团身而上，发起反攻，结果堪堪打中了$P。\n",
				});
				return str[random(sizeof(str))];
    		}
	}
}

/*
"attack"      : "攻击命中率",        "defense"      : "攻击闪避率",
"spells_succ" : "法术命中率",        "spells_dodge" : "法术闪避率",
"combat_succ" : "物理命中率",        "combat_dodge" : "物理闪避率",
"combat_parry": "物理招架率",
*/
varargs int skill_power(object ob, string skill, int usage)
{
	int level,pp;
    	string msg = "";
    	if( !ob || !living(ob) ) return 0;
	//有效等级的好处
    	level = ob->query_skill(skill);
    	if( level<=0 )
        	level = 0;
    	pp = 0;
    	switch(usage)
    	{
    		case SKILL_USAGE_ATTACK:
        		pp = ob->query_temp("apply/attack");		//攻击命中率
        		pp+= ob->query_temp("apply/combat_succ");	//物理命中率
        		break;
    		case SKILL_USAGE_SPELL:
        		pp = ob->query_temp("apply/spells_succ");	//法术命中率
        		pp+= ob->query_temp("apply/attack");		//攻击命中率
        		break;
        	case SKILL_USAGE_DEFENSE:
        		pp = ob->query_temp("apply/defense");		//攻击闪避率
        		pp+= ob->query_temp("apply/combat_dodge");      //物理闪避率
        		break;
        	case SKILL_USAGE_SPELL_DEFENSE:
        		pp = ob->query_temp("apply/spells_dodge");	//法术闪避率
        		pp+= ob->query_temp("apply/defense");	        //攻击闪避率
        		break;
        	case SKILL_USAGE_PARRY:
        		pp = ob->query_temp("apply/combat_parry");	//物理招架率
        		break;
    	}
    	//回风返火 攻击命中+10%
	if( ob->query_skill("huifeng-fanhuo",2)>100 )
		pp = pp+(ob->query_skill("huifeng-fanhuo",1)-100)/200+10;
	//御风	命中+5%
	if( ob->query_skill("yufeng",2)>100 )
		pp = (ob->query_skill("yufeng",1)-100)/100+5;
    	level = level*(100+pp)/100;
    	if( !level )
    		return 0;

    	msg+= HIR+ob->query("id")+NOR"eff_skill_level="+level;
	// 门派技能
    	pp = 100;
    	pp+= FAMILY_D->family_score(ob,skill);
    	level = level*pp/100;
    	msg+= "  门派加成后="+level;
    	msg+= "  valid后="+level;
	if( ob->is_busy() )
    	{
        	level = level-level/3;
        	msg+= "  busy状态损耗后="+level;
    	}
    	level+= ob->query_level()*8;
    	msg+= "  最后取值："+level+"\n";
    	if( environment(ob) && environment(ob)->query("combat_room") )
        	tell_room(environment(ob),msg);
	if( usage )
	{
		if( usage==SKILL_USAGE_SPELL )
			level+= ob->query("daoxing")/5000;
		else if( usage==SKILL_USAGE_SPELL_DEFENSE )
			level+= ob->query("daoxing")/8000;
	}
    	return level;
}

//0--全部 1---只显示命中  2---只显示伤害  3---清爽版
varargs int query_message_type(object who,object victim)
{
	if( who && who->query("env/brief_message")==3 )
		return 3;
	if( victim && victim->query("env/brief_message")==3 )
		return 3;
	if( who && who->query("env/brief_message")==2 )
		return 2;
	if( victim && victim->query("env/brief_message")==2 )
		return 2;
	if( who && who->query("env/brief_message")==1 )
		return 1;
	if( victim && victim->query("env/brief_message")==1 )
		return 1;
	return 0;
}

int attack_percent(object me,object victim,mixed attack_type)
{
	int ap,dp,pp,bjp=0;
	object weapon,weapon2;
	mapping my_action,his_action;
	string bskill,attack_skill,def_skill,bskill2,attack_skill2;

	if( !attack_type || !intp(attack_type) )
        	attack_type = TYPE_COMBAT;
	if( attack_type==TYPE_CAST )
	{
		attack_skill = me->query_skill_mapped("spells");
		if( !attack_skill || !stringp(attack_skill) )
			attack_skill = "spells";
		ap = skill_power(me, attack_skill, SKILL_USAGE_SPELL);
		if( ap<1 ) ap = 1;
		ap+= ap/3;
        	if( family_restrain(me,victim)==1 )
        		ap+= ap/5;
		else if( family_restrain(me,victim)==-1 )
        		ap-= ap/5;
		def_skill = victim->query_skill_mapped("spells");
		if( !def_skill || !stringp(def_skill) )
			def_skill = "spells";
		dp = skill_power(victim, def_skill, SKILL_USAGE_SPELL_DEFENSE);
		if( dp<1 ) dp = 1;
		if( victim->is_busy() )
			dp = dp-dp/5;
		if( !living(victim) )
			dp = 0;
		ap = FAMILY_D->shentong_combat_ap(me,victim,ap);
		//解厄 闪避+10%
		if( victim->query("jiee",2)>100 )
		{
			pp = 10;
			pp+= (victim->query_skill("jiee",1)-100)/250;
			dp = dp*(100+pp)/100;
		}
		//新人福利
		if( userp(me) && me->query_level()<40 )
			ap = ap*3+1;

		if( random(ap+dp)>=dp || check_level(me,victim)==1 )
			return 1;
		else	return RESULT_DODGE;
	}
        if( victim->query_temp("jldl") && living(victim) )
	{
		attack_skill = me->query_skill_mapped("force");
		if( !attack_skill )
			attack_skill = "force";
       		ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK);
        	if( ap<1 ) ap = 1;
		def_skill = victim->query_skill_mapped("force");
		if( !def_skill )
			def_skill = "force";
        	dp = skill_power(victim, def_skill, SKILL_USAGE_DEFENSE);
        	if( dp<1 ) dp = 1;
		ap = FAMILY_D->shentong_combat_ap(me,victim,ap);
		if( family_restrain(me,victim)==1 )
        		ap+= ap/5;
		else if( family_restrain(me,victim)==-1 )
        		ap-= ap/5;
		//解厄 闪避+10%
		if( victim->query("jiee",2)>100 )
		{
			pp = 10;
			pp+= (victim->query_skill("jiee",1)-100)/250;
			dp = dp*(100+pp)/100;
		}
		//新人福利
		if( userp(me) && me->query_level()<40 )
			ap = ap*3+1;

        	if( (random(ap+dp)>ap && check_level(me,victim)!=1 )
        	 || (check_level(me,victim)==-1 && living(victim)) )
    			return RESULT_FORCE;
	}

        my_action = me->query("actions");
    	if( !my_action || !mapp(my_action) )
        	return -2013;

    	his_action = victim->query("actions");
    	if( !his_action || !mapp(his_action) )
        	return -2013;

	if( me->query_temp("anger")>99 && check_level(me,victim)!=-1 )
	{
		bjp = me->query_temp("apply/baoji");
            	if( bjp<1 )  bjp = 1;
            	if( bjp>100 ) bjp = 100;
            	if( random(50+bjp)>=50 )
                	return -1979;
        }

	weapon = me->query_temp("weapon");
	if( weapon && objectp(weapon) )
    	{
        	if( weapon->query("use_apply_skill") )
            		bskill = weapon->query("use_apply_skill");
		else    bskill = weapon->query("skill_type");
	}
    	else    bskill = "unarmed";
    	attack_skill = me->query_skill_mapped(bskill);
	if( !attack_skill || !stringp(attack_skill) )
		attack_skill = bskill;
	ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK);
	if( ap<1 ) ap = 1;
        if( me->query("force_factor")==0 )
        	ap+= ap/10;
        if( attack_type==TYPE_PERFORM )
        	ap*= 2;
        else if( attack_type==TYPE_QUEST )
        	ap*= 3;
        if( family_restrain(me,victim)==1 )
        	ap+= ap/5;
	else if( family_restrain(me,victim)==-1 )
        	ap-= ap/5;
        if( ap<1 ) ap = 1;

	dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);
	if( check_level(me,victim)==1 )
		dp/= 10;
	if( dp<1 ) dp = 1;
	dp+= dp*my_action["dodge"]/100;
	ap = FAMILY_D->shentong_combat_ap(me,victim,ap);

	//解厄 闪避+10%
	if( victim->query("jiee",2)>100 )
	{
		pp = 10;
		pp+= (victim->query_skill("jiee",1)-100)/250;
		dp = dp*(100+pp)/100;
	}
	//新人福利
	if( userp(me) && me->query_level()<40 )
		ap = ap*3+1;

	if( random(ap+dp)<dp || ( attack_type!=TYPE_QUEST && check_level(me,victim)==-1 && living(victim) ) )
		return RESULT_DODGE;
	else
	{
		dp = skill_power(victim, "parry", SKILL_USAGE_PARRY);
		dp+= dp*my_action["parry"]/100;
		if( victim->is_busy() )
			dp = dp-dp/5;
		if( !living(victim) )
			dp = 0;
		if( dp<0 ) dp = 1;
		if( random(ap+dp)<dp || ( attack_type!=TYPE_QUEST && check_level(me,victim)==-1 && living(victim) ) )
			return RESULT_PARRY;
		else	return 1;
	}
}

//伤害反弹函数
string on_hit(object who,object attacker,int damage,int wounded,string receive_type,mixed attack_type)
{
	object weapon;
	int re_damage;
	string tmp,result = "$N受到";
	if( !who || !attacker || !who->is_fighting(attacker) )
		return 0;
	if( who->query("mana")<100
	 || !living(who)
	 || !living(attacker) )
		return 0;
	if( attack_type==TYPE_CAST )
		re_damage =who->query_temp("apply/re_spells_damage");
	else //神通支离	持剑时反弹伤害1%
	{
		re_damage = who->query_temp("apply/re_combat_damage");
		if( who->query_skill("zhili",2)>100
		 && objectp(weapon=who->query_temp("weapon"))
		 && weapon->query("skill_type")=="sword" )
			re_damage+= ((who->query_skill("zhili",1)-100)/300)+1;
	}
	if( re_damage<1 )
		return 0;

	if( re_damage>100 )
		re_damage = 100;
	damage = damage*re_damage/100+1;
	who->add("mana",-10-random(10));
	if( receive_type!="sen" )
	{
		re_damage = attacker->receive_damage("kee",damage,who,attack_type);
		result+= HIR+re_damage+NOR"点气血伤害反弹";
	}
	if( receive_type!="kee" )
	{
		re_damage = attacker->receive_damage("sen",damage,who,attack_type);
		if( result!= "$N受到" )
			result+= "，";
		result+= HIR+re_damage+NOR"点精神伤害反弹。\n";
	}
	if( who->query("mana")<200 || wounded<1 )
	{
		if( query_message_type(who,attacker)==3 )
			;
		else if( query_message_type(who,attacker)!=2 )
       			result = re_damage_msg(who)+result;
		return result;
	}

	if( attack_type==TYPE_CAST )
		re_damage = who->query_temp("apply/re_spells_effdamage");
	else //神通支离	持剑时反弹伤害1%
	{
		re_damage = who->query_temp("apply/re_spells_effdamage");
		if( who->query_skill("zhili",2)>200
		 && objectp(weapon=who->query_temp("weapon"))
		 && weapon->query("skill_type")=="sword" )
			re_damage+= ((who->query_skill("zhili",1)-200)/400)+1;
	}
	if( re_damage<1 )
		return result;


	tmp = "$N受到";
       	if( re_damage>100 )
		re_damage = 100;
	wounded = wounded*re_damage/200+1;
	who->add("mana",-50-random(30));
	if( receive_type!="sen" )
	{
		wounded = attacker->receive_wound("kee",wounded,who,attack_type);
		tmp+= HIR+wounded+NOR"点气血损伤反弹";
	}
	if( receive_type!="kee" )
	{
		wounded = attacker->receive_damage("sen",wounded,who,attack_type);
		if( tmp!= "$N受到" )
			tmp+= "，";
		tmp+= HIR+wounded+NOR"点精神损伤反弹。\n";
	}

	if( query_message_type(who,attacker)==3 )
		;
	else if( query_message_type(who,attacker)!=2 )
       		tmp = re_damage_msg(who)+tmp;
       	result+= tmp;
	return result;
}

varargs int do_attack(object me, object victim, object weapon, mixed attack_type,string combat_msg,string succ_msg,string limb,int damage1,string receive_type)
{
	mapping my, your, action, victim_action;
    	string *limbs, result,temp,clr;
    	string attack_skill, force_skill, dodge_skill, parry_skill;
    	int pp,mod_val,defense_factor,vfp,afp,force_adj,damage, damage_bonus,fbp,my_p,his_p;
    	mixed foo;
    	int wounded = 0;
    	int bjp = 0;
    	int i;

	baoji = 0;
    	if( !me || !victim )
        	return 0;
    	if( me->is_ghost() || victim->is_ghost() )
        	return 1;
    	if( !attack_type || attack_type<0 || attack_type>8 )
        	attack_type = TYPE_COMBAT;
        me->set_temp("last_attack_type",attack_type);
	if( attack_type!=TYPE_QUEST )
	{
    		if( environment(me)->query("no_fight") )
    		{
        		message_vision("$N和$n各自退了一步，收住了招。\n", me, victim);
    			me->remove_enemy(victim);
    			victim->remove_enemy(me);
    			return 0;
    		}
    		if( environment(me) != environment(victim) )
    		{
	        	me->remove_enemy(victim);
    			victim->remove_enemy(me);
    			return 0;
    		}
    	}
    	my = me->query_entire_dbase();
    	your = victim->query_entire_dbase();

    	action = me->query("actions");
    	if( !action || !mapp(action) )
    	{
        	me->reset_action();
        	action = me->query("actions");
        	if( !action || !mapp(action) )
        	{
        		me->remove_enemy(victim);
    			victim->remove_enemy(me);
            		return 0;
            	}
    	}
    	victim_action = victim->query("actions");
    	if( !victim_action || !mapp(victim_action) )
    	{
        	victim->reset_action();
        	victim_action = victim->query("actions");
        	if( !victim_action || !mapp(victim_action) )
            	{
        		me->remove_enemy(victim);
    			victim->remove_enemy(me);
            		return 0;
            	}
    	}
    	if( !arrayp(limbs=victim->query_temp("apply/limbs")) )
    		limbs = victim->query("limbs");
    	if( !limbs || !arrayp(limbs))
    	{
    		if( victim->query("race")!="野兽" )
        		limbs = ({
                        	"头部", "颈部", "胸口", "后心", "左肩", "右肩", "左臂",
                        	"右臂", "左手", "右手", "腰间", "小腹", "左腿", "右腿",
                        	"左脚", "右脚"
                	});
                else	limbs = ({
                		"头部","尾巴","前脚","后脚","屁股","嘴巴","后背",
                	});
        	victim->set("limbs", limbs);
    	}
    	if( !limb || member_array(limb,limbs)==-1 )
    		limb = limbs[random(sizeof(limbs))];

    	if( stringp(combat_msg) )
    	{
		result = combat_msg;
		if( !me->query_temp("pfm_msg") )
   			result+= action["action"];
   	}
	else
	{
		result = "";
		if( !me->query_temp("pfm_msg") )
    		{
			if( me->query_temp("action_flag") )
        			result+= "紧跟着";
   			result+= action["action"];
   		}
		if( query_message_type(me,victim)>=2 )
    			result ="";
    	}
	temp = COLOR_D->clean_color(result);
	i = strlen(temp);
	if( i>2 && temp[i-1..i]!="\n" )
		result+= "。\n";
	temp = "";
	if( attack_type==TYPE_CAST )
		attack_skill = "spells";
	else
	{
		if( weapon && objectp(weapon) )
    		{
        		if( weapon->query("use_apply_skill") )
            			attack_skill = weapon->query("use_apply_skill");
			else    attack_skill = weapon->query("skill_type");
		}
    		else    attack_skill = "unarmed";
    	}
    	attack_skill = me->query_skill_mapped(attack_skill);
	if( !attack_skill || !stringp(attack_skill) )
	{
		if( attack_type==TYPE_CAST )
			attack_skill = "spells";
		else	attack_skill = "unarmed";
	}
	pp = attack_percent(me,victim,attack_type);
	if( wizardp(me) && me->query("env/test") )
		tell_object(me,"命中判断返回"+pp+"  攻击模式为:"+attack_type+"\n");
	if( pp==-2013 )
	{
		me->remove_enemy(victim);
		victim->remove_enemy(me);
            	return 0;
	}

    	else if( pp==RESULT_FORCE )
    	{
        	foo = "/daemon/class/puti/wuxiangforce/jldl.c"->jldl_result(victim, me, mod_val, force_adj,action);
       		if( foo && stringp(foo) )
       			result += foo;
		damage = RESULT_FORCE;
    	}
    	else if( pp==RESULT_DODGE )
    	{
		if( !me->query_temp("pfm_msg") )
        	{
        		if(living(victim))
        			dodge_skill = victim->query_skill_mapped("dodge");
        		else    dodge_skill = 0;
	        	if( !dodge_skill )
        	    	{
                		dodge_skill = "dodge";
                		if( query_message_type(me,victim)<1 )
               				result+= SKILL_D(dodge_skill)->query_dodge_msg(limb);
			}
        	    	else
            		{
            			if( query_message_type(me,victim)<1 )
            			{
               				if( victim_action && victim_action["dodge_action"] )
	                    			result+= victim_action["dodge_action"];
					else    result+= SKILL_D(dodge_skill)->query_dodge_msg(limb);
				}
			}
		}
            	if( dodge_skill && stringp(dodge_skill) )
		{
                	foo = SKILL_D(dodge_skill)->hit_ob(victim,me);
			if( stringp(foo) && query_message_type(me,victim)<3 )
                    		result+= foo;
		}
		if( ( !userp(victim) || !userp(me) )
                 && random(sizeof(victim->query_enemy())) < 4
            	 && random(your["sen"]*100/victim->query_maxsen()+ your["int"]*your["cps"]) > 150 )
		{
                	victim->add("combat_exp",1);
                	victim->improve_skill("dodge", 1);
		}
            	if( !userp(me) )
		{
                	if( random(my["int"]) > 15 )
                    		me->add("combat_exp",1);
			me->improve_skill(attack_skill, random(my["int"]));
		}
            	damage = RESULT_DODGE;
	}
    	else if( pp==RESULT_PARRY )
    	{
    		parry_skill = victim->query_skill_mapped("parry");
    		if( !parry_skill ) parry_skill = "parry";
		dodge_skill = SKILL_D(parry_skill)->query_parry_msg(victim,me);
                if( query_message_type(me,victim)<1 && !me->query_temp("pfm_msg") )
                {
                		if( dodge_skill )
                    			result+= dodge_skill;
				else    result+= SKILL_D("parry")->query_parry_msg(victim,me);
		}
                if( parry_skill && stringp(parry_skill) )
		{
                	foo = SKILL_D(parry_skill)->hit_ob(victim,me);
			if( stringp(foo) && query_message_type(me,victim)<3 )
                    		result+= foo;
		}
                if( (!userp(victim) || !userp(me))
		  && random(sizeof(victim->query_enemy())) < 4
                  && random(your["sen"]*100/victim->query_maxsen() + your["int"]*your["cps"]) > 150 )
		{
                	victim->add("combat_exp",1);
                    	victim->improve_skill("parry", 1);
		}
		if( !userp(me) )
		{
                	if( random(my["int"]) > 15 )
                    		me->add("combat_exp",1);
			me->improve_skill(attack_skill, random(my["int"]));
		}
                damage = RESULT_PARRY;
    	}
    	else
	{
		if( !receive_type || !stringp(receive_type)
		 || ( receive_type!="kee" && receive_type!="sen" && receive_type!="both" ) )
		{
			switch(attack_type)
			{
				case TYPE_CAST : receive_type = "sen";break;
				default: receive_type = "kee";break;
			}
		}
		if( succ_msg && stringp(succ_msg) && query_message_type(me,victim)<2 )
                	result+= succ_msg;

                damage = valid_damage(me,victim,attack_skill,attack_type);

                if( attack_type!=TYPE_CAST )
                {
                	if( !undefinedp(action["damage"]) )
                    		damage += action["damage"] * damage/100;
		}
                else
                {
                	foo = SKILL_D(attack_skill)->base_damage();
                    	if( foo )
                    	{
                    		if( intp(foo) && foo>0 )
                    			damage+= damage*foo/100;
			}
		}
                foo = me->hit_ob(me, victim, damage,attack_type);
                if( stringp(foo) && query_message_type(me,victim)<2 )
                	result += foo;
		else if(intp(foo) )
			damage += foo;
		if( attack_skill && stringp(attack_skill) )
                {
                	foo = SKILL_D(attack_skill)->hit_ob(me, victim, damage);
                    	if( stringp(foo) && query_message_type(me,victim)<2 )
                    		result+= foo;
			else if(intp(foo) )
                    		damage+= foo;
		}
                if( weapon )
                {
                	foo = weapon->hit_ob(me, victim, damage);
                    	if( stringp(foo) && query_message_type(me,victim)<2 )
				result += foo;
			else if(intp(foo) )
                    		damage+= foo;
		}
                if( attack_type!=TYPE_CAST )
                {
                	if( weapon )
                		damage_bonus = damage/5;
			else	damage_bonus = 0;
		}
                if( attack_type==TYPE_CAST )
                {
	        	damage_bonus+= me->query("mana_factor")/10+me->query_spi();
        	        damage_bonus+= me->query("mana")/30;
		}
                else
                {
                	damage_bonus+= me->query("force_factor")/10+me->query_str();
                	damage_bonus+= me->query("force")/30;
		}
                damage_bonus = damage_bonus/3+random(damage_bonus/3);
		if( attack_type!=TYPE_CAST )
                {
                	if( !undefinedp(action["force"]) )
                    		damage_bonus = action["force"] *damage_bonus/300;
			else	damage_bonus = 0;
		}
                if( damage_bonus>0 && my["force_factor"] && (my["force"] > my["force_factor"]) && attack_type!=TYPE_CAST )
                {
                	if( force_skill = me->query_skill_mapped("force") )
                    	{
                        	foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["force_factor"]);
                       		if( stringp(foo) && query_message_type(me,victim)<2 )
                       			result += foo;
				else if( intp(foo) ) damage_bonus += foo;
			}
		}
                if( damage < 1 ) damage =1;
                //暴击
                if( pp==-1979 )
		{
                	damage = damage*3;
                    	damage_bonus = damage_bonus*2;
                    	damage_bonus = damage_bonus/2+random(damage_bonus/2);
                    	damage = damage/2+random(damage/2);
               		me->set_temp("anger",0);
			if( query_message_type(me,victim)<2 )
                		result+= BLINK HIY"$N"BLINK HIY"怒气冲天，打出了一击暴击！\n"NOR;
		}
		// 根据攻击的部位影响伤害
               	if( !undefinedp(limb_damage[limb]) )
                	damage = (damage * limb_damage[limb] / 100);
                //法宝
		if( damage>0 )
		{
			if( objectp(foo = me->query_temp("armor/Fabao"))
			&& foo->query_temp("jiing") )
			{
				foo = foo->hit_ob(me,victim,attack_type);
				if( foo && stringp(foo) )
					result+= foo;
			}
		}
		if( damage>50 )
		{
			if( objectp(foo=victim->query_temp("armor/Fabao"))
			&& foo->query_temp("jiing") )
			{
				fbp = 0;
               			if( attack_type==TYPE_CAST )
               				fbp = foo->protect_shen(damage);
				else	fbp = foo->protect_qi(damage);
				if( damage!=fbp )
				{
                    			foo = foo->protect_msg();
                    			if( stringp(foo) )
                    				result+= foo;
				}
                        	damage = fbp;
			}
		}
                //法宝end
                if( damage<0 )
                	damage = 0;
                if( check_level(me,victim)==-1 )
		{
			if( damage>0 ) damage = 1;
		}
		if( query_message_type(me,victim)<2 && (!me->query_temp("pfm_msg") || !succ_msg) )
                {
                	if( attack_type==TYPE_CAST )
                		result+= damage_msg(damage, "法术");
			else	result+= damage_msg(damage, action["damage_type"]);
		}
		damage1 = damage+damage1;
		if( me->query("env/tests") )
			tell_object(me,sprintf(WHT"damage1="HIR"%d"NOR"\n",damage1));
		temp = "结果对$n造成了";
		if( receive_type!="sen" )
		{
			damage = victim->receive_damage("kee",damage1,me,attack_type);
			if( me->query("env/tests") )
			tell_object(me,sprintf(WHT"damage="HIR"%d"NOR"\n",damage));
			if( damage>0 )
				temp+= HIR+damage+NOR"点气血减少";
		}
		if( receive_type!="kee" )
		{
			damage = victim->receive_damage("sen",damage1,me,attack_type);
			if( damage>0 )
			{
				if( temp != "结果对$n造成了" )
					temp+= "，";
				temp+= HIR+damage+NOR"点精神减少";
			}
		}
		damage1 = damage;
		if( damage_bonus>0 && me->is_killing(victim->query("id")) )
		{
			if( receive_type!="sen" )
			{
				wounded = victim->receive_wound("kee",damage_bonus, me,attack_type);
				if( wounded>0 )
				{
					if( temp != "结果对$n造成了" )
						temp+= "，"HIR+wounded+NOR"点气血损伤";
					else	temp+= HIR+wounded+NOR"点气血损伤";
				}
			}
			if( receive_type!="kee" )
			{
				wounded = victim->receive_wound("sen",damage_bonus, me,attack_type);
				if( wounded>0 )
				{
					if( temp != "结果对$n造成了" )
						temp+= "，"HIR+wounded+NOR"点精神损伤";
					else	temp+= HIR+wounded+NOR"点精神损伤";
				}
			}
		}
                if( damage>10 )
                {
                	switch( limb )
            		{
                		case "头部":
                        	case "颈部":// 头、颈受伤会伤一些神。
                            		damage /= 5;
                            		if( victim->query_temp("armor/FABAO") )
                            		{
                                		fbp = victim->query_temp("armor/FABAO")->protect_shen(damage);
                                		if( fbp>=150 )
                                    			damage = fbp;
					}
                            		victim->receive_damage("sen", damage, me ,attack_type);
                			fbp = victim->query("sen")*100/victim->query_maxsen();
                			if( query_message_type(me,victim)<=1 )
                			{
                            			if( fbp <= 30 )
                    					result+= head_damage_me_msg[2];
						else if( fbp<= 70 )
                    					result+= head_damage_me_msg[1];
						else    result+= head_damage_me_msg[0];
					}
                            		break;
				case "胸口":// 击中这些部位真气会受到振荡。
                        	case "后心":
                		case "小腹":
                			if( victim->query_maxforce()>0 && victim->query("force")>0 )
                            		{
                            			damage /= 8;
	                            		if( victim->query("force") <= (damage/3+1) )
							victim->set("force", 0);
						else	victim->add("force", -damage/3-1);
						if( query_message_type(me,victim)<=1 )
						{
	                	        		if( damage <= 500 )
        	                				result+= body_damage_me_msg[0];
							else if( damage <= 1000 )
                        	    				result+= body_damage_me_msg[1];
							else	result+= body_damage_me_msg[2];
						}
					}
					break;
			}
		}
		if( check_level(me,victim)==-1 )
			if( damage_bonus>0 ) damage_bonus = 0;


		//神通：回天返日 穿射效果
		if( me->query_skill("huitian-fanri",2)>0
		 && receive_type!="sen" )
		{
			int cdamage = damage1;
			object tar,*victims = me->query_enemy();
			i = me->query_skill("huitian-fanri",1)/300;
			if( i<1 ) i=1;
			i = 1+random(i);
			if( i>3 ) i = 3;
			while(i--)
			{
				if(cdamage>10)
				{
					cdamage/= 10;
					tar = victims[random(sizeof(victims))];
					if( me->is_fighting(tar) )
					{
						cdamage = tar->receive_damage("kee",cdamage,me,attack_type);
						if( tar==victim )
							result+= "对$n造成了"HIR+cdamage+NOR"点穿刺伤害。\n";
						else	result+= "对"+tar->name()+"造成了"HIR+cdamage+NOR"点气血穿刺伤害。\n";
					}
				}
			}
		}
		//神通：九息服气 吸血效果
		if( me->query_skill("jiuxi-fuqi",2)>0
		 && receive_type!="sen" )
		{
			i = me->query_skill("jiuxi-fuqi",1)/10;
			if( i>damage1/10 )
				i = damage1/10;
			me->receive_curing("kee",i);
			result+= "结果$N治疗了"HIR+i+NOR"点气血。\n";
		}

                // 由于受到伤害，victim产生愤怒，愤怒值随着伤害大小而变
                if( damage > victim->query_maxkee()/10)
                	victim->add_temp("anger",1+random(5));
		else    victim->add_temp("anger",1);
                if( !userp(me) || !userp(victim) )
                {
                	if( random(my["sen"]*100/me->query_maxsen() + my["int"]*my["cps"]) > 150 )
			{
                        	me->add("combat_exp",1);
                        	if( my["potential"] - my["learned_points"] < 100 )
                            		my["potential"] += 1;
				me->improve_skill(attack_skill, 1);
			}
			if( random(victim->query_maxkee() + your["kee"]) < damage )
                    	{
                        	victim->add("combat_exp",1);
                        	if( your["potential"] - your["learned_points"] < 100 )
                            		your["potential"] += 1;
			}
		}
//////////////////////////
	}

	result = replace_string( result, "$l", limb );
    	if( !undefinedp(action["weapon"]) && stringp(action["weapon"]) )
        	result = replace_string( result, "$w", action["weapon"] );
	else if( objectp(weapon) )
        	result = replace_string( result, "$w", COLOR_D->clean_color(weapon->name()) );
	else if( attack_skill == "unarmed" || attack_skill == "unarmed")
        	result = replace_string(result, "$w", "手指" );
	else if( attack_skill == "strike" || attack_skill == "parry")
		result = replace_string(result, "$w", "手掌" );
	else    result = replace_string(result, "$w", "拳头" );
	if( objectp(victim->query_temp("weapon")) )
        	result = replace_string( result, "$W",COLOR_D->clean_color(victim->query_temp("weapon")->name()) );
	else    result = replace_string( result, "$W","双掌");
    	if( (damage<=0 && query_message_type(me,victim)>0)
    	 || query_message_type(me,victim)==3 )
    		;
	else
	{
		clr = me->query_temp("pfm_color");
                if( clr && stringp(clr) )
                {
                	result = COLOR_D->clean_color(result);
			result= clr+result+NOR;
			result = COLOR_D->replace_color(result,2);
		}
		if( query_message_type(me,victim)==2 )
			result+= temp;
		message_vision(result,me,victim);
    	}

	if( damage > 0 )
    	{
        	if( receive_type!="sen" )
        	{
        		report_status(victim);
        		if( wounded>0 )
            			report_status(victim, wounded);
            	}
            	if( receive_type!="kee" )
            		report_sen_status(victim, wounded);

		//伤害反弹
		if( stringp(result = on_hit(victim,me,damage1,wounded,receive_type,attack_type)) )
		{
			message_vision(result,me,victim);
			report_status(me);
			if( wounded )
				report_status(me,1);
		}


		if( me && living(me) && victim
		&& me->is_fighting(victim)
		&& me->query_temp("last_attack_type")!=TYPE_QUICK
		&& me->query_temp("last_attack_type")!=TYPE_QUEST )
		{
			if( attack_type!=TYPE_CAST )
			{
				if( me->query_temp("pfm_action") )
					("/quest/family/family_pfm.c")->attack_action(me,victim,me->query_temp("weapon"),damage);
			}
			else if( me->query_temp("cast_action") )
				("/quest/family/family_pfm.c")->attack_cast_action(me,victim,me->query_temp("weapon"),damage);
		}

        	if( me->is_busy() ) me->interrupt_me(me, 30 + random(10));
        	if( (!me->is_killing(your["id"])) && (!victim->is_killing(my["id"])) )
    		{
        		if( victim->query("kee") < victim->query_maxkee()*50 / 100)
        		{
            			me->remove_enemy(victim);
        			victim->remove_enemy(me);
        			message_vision( winner_msg[random(sizeof(winner_msg))], me, victim);
        			if( userp(me) && !userp(victim) )
        				victim->combat_lose(me);
        			if( userp(victim) && !userp(me) )
        				me->combat_win(victim);
            		}
        	}
    	}
    	if( functionp(action["post_action"]) && attack_type!=TYPE_CAST )
        	evaluate( action["post_action"], me, victim, weapon, damage);

	if( attack_type==TYPE_REGULAR
     	 && damage < 1
     	 && victim->query_temp("guarding") )
    	{
        	victim->set_temp("guarding", 0);
        	if( random(my["cps"]) < 5 )
        	{
        		if( query_message_type(me,victim)<1 )
            			message_vision(CYN"$N"NOR CYN"一击不中，露出了破绽！\n"NOR, me);
            		do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);
        	}
        	else
        	{
        		if( query_message_type(me,victim)<1 )
            			message_vision(WHT"$N"NOR WHT"见$n"NOR WHT"攻击失误，趁机发动攻击！\n"NOR, victim, me);
            		do_attack(victim, me, victim->query_temp("weapon"), TYPE_RIPOSTE);
        	}
    	}
    	return damage;
}

void fight(object me, object victim)
{
	object ob;

    	if( !living(me) || !victim )
        	return;
    	if( userp(me) && me->query_temp("netdead") && !me->query_temp("pkmeet/begin") )
        	return;
    	if( userp(victim) && victim->query_temp("netdead") && !victim->query_temp("pkmeet/begin"))
    	{
        	if( member_array( me, victim->query_netdead_enemy() ) == -1 )
            		return;     // can't start fight if the victim is already netdead
    	}
	if( victim->is_busy() || victim->is_blind() || !living(victim)
	 || victim->is_no_move() )
    	{
        	me->set_temp("guarding", 0);
        	if( !victim->is_fighting(me) )
        		victim->fight_ob(me);
        	do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
    	}
    	else if( random( (int)victim->query("cps") * 3 ) < ((int)me->query("cor") + (int)me->query("bellicosity") / 50) )
    	{
        	me->set_temp("guarding", 0);
        	if( !victim->is_fighting(me) ) victim->fight_ob(me);
        	do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);
    	}
    	else if( !me->query_temp("guarding") )
    	{
        	me->set_temp("guarding", 1);
        	if( !me->query("env/brief_message") && !victim->query("env/brief_message") )
			message_vision( guard_msg[random(sizeof(guard_msg))], me, victim);
    	}
    	else	return;
}

//  auto_fight()
void auto_fight(object me, object obj, string type)
{
    if( !userp(me) && !userp(obj) ) return;
    if( me->query_temp("looking_for_trouble") ) return;
    me->set_temp("looking_for_trouble", 1);
    call_out( "start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
    	int bellicosity;
    	if( !me )
    		return;// Are we still exist( not becoming a corpse )?
    	me->set_temp("looking_for_trouble", 0);
    	if( !obj || wizardp(obj) || !living(obj) )
    		return;
    	if( me->is_fighting(obj)        // Are we busy fighting?
    	 || !living(me)             // Are we capable for a fight?
    	|| environment(me)!=environment(obj)   // Are we still in the same room?
    	|| environment(me)->query("no_fight") )  // Are we in a peace room?
        	return;
	if( check_level(me,obj)==-1
	 || ( obj->query("name")==me->query("family/master_name")
	   && obj->query("id")==me->query("family/master_id") ) )
		return;
	if( !valid_kill(me,obj,0) )
		return;
    	bellicosity = (int)me->query("bellicosity");
    	message_vision(RED"\n$N"RED"用一种异样的眼神扫视着在场的每一个人。\n"NOR, me);
    	if( (int)me->query("force") > (random(bellicosity) + bellicosity)/2 )
        	return;
    	if( random(bellicosity)>me->query_level()*100 &&  !wizardp(obj) )
    	{// auto kill, mark my_killer_list. -- mon 9/23/98
        	message_vision(HIW"\n$N"HIW"对着$n"HIW"喝道：" + RANK_D->query_self_rude(me)+ HIW"看你实在很不顺眼，去死吧。\n"NOR, me, obj);
        	me->set_temp("kill/target/"+obj->query("id"),1);
        	me->kill_ob(obj);
    	}
    	else
    	{
        	message_vision(HIW"\n$N"HIW"对着$n"HIW"喝道：喂！" + RANK_D->query_rude(obj)+ HIW"，" + RANK_D->query_self_rude(me) + HIW"正想找人打架，陪我玩两手吧！\n"NOR,me, obj);
        	me->fight_ob(obj);
    	}
}

void start_hatred(object me, object obj)
{
    	if( !me || !obj ) return;           // Are we still exist( not becoming a corpse )?
    	me->set_temp("looking_for_trouble", 0);
    	if( me->is_fighting(obj)        // Are we busy fighting?
    	|| !living(me)             // Are we capable for a fight?
    	|| environment(me)!=environment(obj)   // Are we still in the same room?
    	|| environment(me)->query("no_fight") )  // Are we in a peace room?
        	return;
    	message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
    	me->kill_ob(obj);
}

void start_vendetta(object me, object obj)
{
    	if( !me || !obj ) return;           // Are we still exist( not becoming a corpse )?
    	me->set_temp("looking_for_trouble", 0);
    	if( me->is_fighting(obj)        // Are we busy fighting?
    	 || !living(me)             // Are we capable for a fight?
    	 || environment(me)!=environment(obj)   // Are we still in the same room?
    	 || environment(me)->query("no_fight") )  // Are we in a peace room?
        	return;
    	me->kill_ob(obj);
}

void start_aggressive(object me, object obj)
{
    	if( !me || !obj ) return;           // Are we still exist( not becoming a corpse )?
    	me->set_temp("looking_for_trouble", 0);
    	if( me->is_fighting(obj)        // Are we busy fighting?
    	 || !living(me)             // Are we capable for a fight?
    	 || environment(me)!=environment(obj)   // Are we still in the same room?
    	 || environment(me)->query("no_fight") )  // Are we in a peace room?
        	return;
    	me->kill_ob(obj);
}

//add by yesi
void start_pkmeet(object me, object obj)
{
	if( !me || !obj ) return;
    	me->set_temp("looking_for_trouble", 0);
    	if( me->is_fighting(obj)        // Are we busy fighting?
    	|| !living(me)             // Are we capable for a fight?
    	|| environment(me)!=environment(obj)   // Are we still in the same room?
    	|| environment(me)->query("no_fight") )  // Are we in a peace room?
        	return;
    	me->kill_ob(obj);
}

void announce(object ob, string event, string msg)
{
    	if(ob->query_temp("pkgame"))
        	return;
    	switch(event)
    	{
        	case "dead":
        		message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n", ob);
        		break;
        	case "unconcious":
        		message_vision("\n$N神志迷糊，脚下一个不稳，倒在地上昏了过去。\n\n", ob);
        		break;
        	case "revive":
        		if( ob->query("blind") || ob->query("race") != "人类")
            			message_vision("\n$N身子一颤，扭动了几下，清醒了过来。\n\n", ob);
            		else if( ob->query("mute"))
            			message_vision("\n$N慢慢清醒了过来，睁开眼睛站起来摇了摇头。\n\n", ob);
            		else    message_vision("\n$N身子动了动，口中呻吟了几声，清醒过来。\n\n", ob);
        		break;
        	case "death_rumor":
        		CHANNEL_D->do_channel(this_object(),"rumor",msg);
        		break;
    	}
}

void winner_reward(object killer, object victim)
{
	killer->defeated_enemy(victim);
}

void killer_reward(object killer, object victim)
{
    	int bls,i,gain,lose,msg_type;
    	string vmark,killmsg,rkmsg,str,killerid;
    	object weapon,fainter;
    	mixed ap,dp;

    	if( userp(victim) )
    	{
        	string *my_killer_list,fam;
        	int init_killer,no_pk;

        	killer->add("PKS", 1);
        	killerid = killer->query("id");
        	my_killer_list = victim->query_killer();
        	if(!my_killer_list )
            		init_killer = -1;
        	else    init_killer = member_array(killerid, my_killer_list);
        	no_pk = killer->query_condition("no_pk_time");
        	if( no_pk>10 ) init_killer=1;
        	killmsg = killer->query_temp("kill_msg");
        	msg_type = 0;
        	if( killmsg )
        	{
            		if( killmsg=="special_msg" ) //特殊的攻击
            		{
                		rkmsg = killer->query_temp("special_msg");
                		killer->delete_temp("special_msg");
                		msg_type = 1;
            		}
            		else
            		{
				if( !undefinedp(KillMsg[killmsg]) )
				{
            				rkmsg=KillMsg[killmsg];
            				msg_type = 2;
            			}
				else
				{
					if( !stringp(fam=killer->query("family/family_name")) )
            					fam = "其他";
            				if( !undefinedp(KillMsg2[fam]) )
            				{
            					if( !undefinedp(KillMsg2[fam][killmsg]) )
            					{
            						rkmsg=KillMsg2[fam][killmsg];
            						msg_type = 3;
            					}
            					else	rkmsg = 0;
            				}
            				else if( !undefinedp(KillMsg2["其他"][killmsg]) && rkmsg==0 )
            				{
            					rkmsg=KillMsg2["其他"][killmsg];
            					msg_type = 3;
            				}
            				else	rkmsg=0;
            			}
			}
        	}
		str = victim->name(1)+HIM"在"+MISC_D->find_place(environment(killer))+HIM"被"+killer->name(1);
		switch(msg_type)
		{
			case 1 : str+= rkmsg+NOR;break;
			case 2 :
				weapon = killer->query_temp("weapon");
				if( weapon )
					str+= HIM"用"HIY+COLOR_D->clean_color(weapon->name())+HIM+rkmsg+"死了。"NOR;
				else	str+= HIM+rkmsg+"死了。"NOR;
				break;
			case 3 : str+= HIM"用一招「"+HIY+rkmsg+HIM"」送去见了崔爷爷。"NOR;break;
			default: str = 0;
		}
    		if( str!=0 )
    			CHANNEL_D->do_channel(this_object(), "rumor",str);

        	if( userp(killer) && init_killer!=-1 )
        	{ // killer is user.
            		killer->apply_condition("no_pk_time",240+no_pk);
            		lose =victim_lose(killer,victim,killerid);
            		gain=lose*2/3;
            		if( gain<0) gain=0;
            		victim->delete_temp("last_fainted_from");
            		if( lose>100)
                		killer->delete("kill/last_killer");
            		victim->set("kill/last_killer",killerid);
            		victim->set("kill/last_lose",gain);
            		victim_penalty(victim);
            		bls=10;
            		log_file("death",XYJTIME_D->chinese_time(ctime(time()))+" "+victim->query("id")+" was killed by "+killerid+".\n");
        	}
        	else
        	{    // killer is not user or killer didn't init the kill.
            		string last_faint;
            		last_faint = victim->query_temp("last_fainted_from");
            		if( last_faint )
            		{
            			fainter = find_player(last_faint);
                    		if( init_killer!=-1)
				{
					if( fainter && fainter!=victim )
                        			fainter->apply_condition("no_pk_time",240+fainter->query_condition("no_pk_time"));
                        		log_file("death",XYJTIME_D->chinese_time(ctime(time()))+" "+victim->query("id")+" was fainted by "+last_faint+" and killed by "+killerid+".\n");
				}
            		}
            		else	log_file("death",XYJTIME_D->chinese_time(ctime(time()))+" "+victim->query("id")+" was killed by "+killerid+".\n");
            		victim_penalty(victim);
            		bls = 10;
        	}
    	}
    	else
    	{  //NPC is the victim.
        	if( userp(killer) )
        	{
            		int reward;
            		reward = nk_gain(killer, victim);
               		if( (int)victim->nk_reward(killer, reward)>0)
               			;
            		else if( reward>0)
            		{
                		killer->add("kill/nkgain",reward);
                		killer->add("daoxing",reward);
                		str = chinese_daoxing(reward);
                		tell_object(killer,HIY"【系统】你得到了"+str+"道行。"NOR"\n");
                		str = sprintf("%s(%d)杀死了%s(%d)，得到%d点道行。", killer->query("id"),killer->query_level(),victim->query("id"),victim->query_level(),reward );
                		log_file("npckill",XYJTIME_D->chinese_time(ctime(time()))+" "+str+"\n");
                		CHANNEL_D->do_channel(this_object(), "sys",str);
            		}
        	}
    		killer->add("MKS", 1);
    		bls = 1;
    	}

	killer->delete_temp("kill_weapon");
        killer->delete_temp("kill_msg");

    	ap = killer->query_level();
    	dp = victim->query_level();

	if( !userp(killer) && ap>dp )
        	bls=1;

    	killer->add("bellicosity", bls * (userp(killer)? 1: 10));
    	if( stringp(vmark = victim->query("vendetta_mark")) )
        	killer->add("vendetta/" + vmark, 1);
    	if( userp(killer)) killer->save();
    	if( userp(victim)) victim->save();
}

void victim_penalty(object victim)
{
	string str,fam;
	int combat_exp_loss,dx_loss;
       	if( !victim )
        	return;

    	if( (int)victim->query_level()<30 )
        	return;

    	//普通百姓
    	if( !fam=victim->query("family/family_name") )
    	{
        	combat_exp_loss = (int)victim->query("combat_exp") /1000;
        	dx_loss = (int)victim->query("daoxing") /1000;
    	}
    	else
    	{
        	switch(fam)
        	{
            		case "南海普陀山" :
	                	if( victim->query("bellicosity")>0 )
        	        	{
                	    		combat_exp_loss = (int)victim->query("combat_exp")/1600;
                    			dx_loss = (int)victim->query("daoxing") /1600;
	                	}
        	        	else
                		{
                    			combat_exp_loss = (int)victim->query("combat_exp")/2000;
                    			dx_loss = (int)victim->query("daoxing") /2000;
	                	}
        	        	break;
            		case "阎罗地府":
                    		combat_exp_loss = (int)victim->query("combat_exp")/1600;
                    		dx_loss = (int)victim->query("daoxing") /1600;
                    		break;
            		case "百花谷":
                    		combat_exp_loss = (int)victim->query("combat_exp")/1000;
                    		dx_loss = (int)victim->query("daoxing") /1000;
                    		break;
            		case "月宫" :
                    		combat_exp_loss = (int)victim->query("combat_exp")/1200;
                    		dx_loss = (int)victim->query("daoxing") /1200;
                    		break;
            		case "五庄观" :
                    		combat_exp_loss = (int)victim->query("combat_exp")/1400;
                    		dx_loss = (int)victim->query("daoxing") /1400;
                    		break;
            		case "将军府" :
                    		combat_exp_loss = (int)victim->query("combat_exp")/1000;
                    		dx_loss = (int)victim->query("daoxing") /1000;
                    		break;
            		case "盘丝洞" :
            		case "火云洞" :
            		case "大雪山" :
            		case "陷空山无底洞" :
                    		combat_exp_loss = (int)victim->query("combat_exp")/800;
                    		dx_loss = (int)victim->query("daoxing") /800;
                    		break;
            		case "方寸山三星洞" :
            		case "东海龙宫" :
            		case "蜀山派" :
            		case "散仙派" :
                    		combat_exp_loss = (int)victim->query("combat_exp")/1300;
                    		dx_loss = (int)victim->query("daoxing") /1300;
                    		break;
            		default :
                    		combat_exp_loss = (int)victim->query("combat_exp")/1000;
                    		dx_loss = (int)victim->query("daoxing") /1000;
                    		break;
        	}
    	}
    	if( combat_exp_loss<0 )
        	combat_exp_loss = 15000000;
    	else if( combat_exp_loss<1000 )
        	combat_exp_loss = 1000;
    	if( dx_loss<0 )
        	dx_loss = 15000000;
    	else if( dx_loss<1000 )
        	dx_loss = 1000;

	victim->set("death/mud_age",victim->query("mud_age"));
	victim->set("death/time",time());
	if( victim->query("daoxing")<dx_loss )
		dx_loss = victim->query("daoxing");
	if( victim->query("combat_exp")<combat_exp_loss )
	{
		if( victim->level_lose() )
		{
			str = " lost 1 level\n";
			tell_object(victim,HIG"【系统】你的等级减少了"HIR"1"HIG"级。\n"NOR);
			victim->add("daoxing", -dx_loss);
			victim->set("death/combat_exp_loss",combat_exp_loss);
   			victim->set("death/dx_loss",dx_loss);
   			str = " lost 1 level points and "+ dx_loss+ " dx points";
			CHAR_D->setup_char( victim );
			UPDATE_D->check_user(victim,1);
			victim->save(1);
		}
	}
	else
	{
	   	victim->add("combat_exp", -combat_exp_loss);
   		victim->add("daoxing", -dx_loss);
   		victim->set("death/combat_exp_loss",combat_exp_loss);
   		victim->set("death/dx_loss",dx_loss);
   		str = " lost "+combat_exp_loss+" exp points and "+ dx_loss+ " dx points";
   	}

    	victim->delete("vendetta");
    	if( victim->query("thief") )
        	victim->set("thief", (int)victim->query("thief") / 2);
    	if( random(100)>random((int)victim->query_kar()) )
    	{
	        victim->set("death/skill_loss",1);
        	victim->skill_death_penalty();
        	str+= " and lost skill";
    	}
    	else    victim->set("death/skill_loss",0);
    	victim->save();
    	str+= "\n";
	str = XYJTIME_D->chinese_time(ctime(time()))+" "+victim->query("id")+str;
   	log_file("death",str);
}

int nk_gain(object killer, object victim)
{
	int eff,lvl,lvl1,level,max,pp,nkgain;
	if(victim->query("no_nk_reward"))
		return 0;
	if(victim->query_temp("last_fainted_from")
         && victim->query_temp("last_fainted_from")!=killer->query("id"))
         	return 0;

	lvl = killer->query_level();
	lvl1 = victim->query_level();
	level = lvl1-lvl;
	if( level<-5 )
		return 0;
	if( level>5 )
	{
		pp = 100+level;
		max = 50000;
	}
	else
	{
		pp = 100;
		max = 20000;
	}
	nkgain = victim->query("nkgain");
	eff = family_restrain(killer,victim);
	if( eff==0 )
		eff = 100;
	else if( eff==-1 )
		eff = 80;
	else	eff = 120;
	eff = (eff+pp)/2;
	if( nkgain>10000 )
		nkgain = nkgain/100*eff;
	else	nkgain = nkgain*eff/100;
	if( nkgain>max )
		nkgain = max;
	return nkgain;
}

int victim_lose(object killer,object victim,string killerid)
{
    	int lose,exp_k,exp_v,lose1;

       	if( (wizardp(victim) && !wizardp(killer))
     	 || (!wizardp(victim)&&wizardp(killer)) )
        	return 0;
       if( victim->query_temp("last_fainted_from")
     	&& victim->query_temp("last_fainted_from")!=killerid )
		lose=0;
       else
       {
       		exp_k = killer->query("daoxing");
          	exp_v = victim->query("daoxing");
          	if( exp_k>exp_v )
          	{
        		lose=10*exp_v/(exp_k+1)*(4000+exp_v)/500;
         		if( exp_k>exp_v*4 )
            			lose=0;
          	}
           	else    lose=(4000+exp_v)/50;  // about 2% lose for victim.
           	if( lose<0 )   lose=0;
           	if( lose>exp_v )       lose=exp_v;
       }
       lose1 = (int)victim->query("daoxing")/40;
       if( lose>lose1 )       lose=lose1;
       return lose;
}
