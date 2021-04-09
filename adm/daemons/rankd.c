// rankd.c
#include <mudlib.h>
#include <ansi.h>
#include <combat.h>
#include <skill_type.h>

//descriptions...

//note, be careful with the size of this list, dx increases as n^3. 
string tough_level(int power);
string gettof(object me, object obj);

string skill_level(string type, int level);
string skill_get_level(string skill, int level);

string *dx_level_desc = ({
        HIB "新入道途" NOR, //in unit of year 
        HIB "闻道则喜" NOR, //1x2=2   
        HIB "初领妙道" NOR, //8x2=16
        HIB "略通道行" NOR, //27x2=56    
        HIB "渐入佳境" NOR, //64x2=128
        CYN "元神初具" NOR, //125x2=250
        CYN "道心稳固" NOR, //216x2=432    
        CYN "一日千里" NOR, //343x2=686
        CYN "道高德隆" NOR, //512x2=1024
        CYN "脱胎换骨" NOR, //729x2=1458    
        HIC "霞举飞升" NOR, //1000x2=2000
        HIC "道满根归" NOR, //1331x2=2662    
        HIC "不堕轮回" NOR, //1728x2=3456
        HIC "已证大道" NOR, //2197x2=4394    
        HIC "反璞归真" NOR, //2744x2=5688 
        HIW "天人合一" NOR  //3375x2=6750
});

string *fali_level_desc = ({
        HIB "初具法力" NOR, 
        HIB "略晓变化" NOR, 
        HIB "降龙伏虎" NOR, 
        HIB "腾云驾雾" NOR, 
	YEL "日行千里" NOR, 
	YEL "化身千万" NOR, 
	YEL "御剑飞行" NOR, 
        YEL "神出鬼没" NOR, 
        CYN "预知祸福" NOR, 
        CYN "妙领天机" NOR, 
        CYN "呼风唤雨" NOR, 
        CYN "负海担山" NOR, 
        CYN "移星换斗" NOR, 
        HIC "包罗万象" NOR, 
        HIC "随心所欲" NOR, 
        HIC "变换莫测" NOR, 
        HIW "法力无边" NOR, 
});

string *exp_level_desc = ({ //41
                HIB "初学乍练" NOR,
                HIB "不知所以" NOR,
                HIB "粗通皮毛" NOR,
                HIB "略识之无" NOR,
                HIB "渐有所悟" NOR,
                YEL "半生不熟" NOR,
                YEL "马马虎虎" NOR,
                YEL "触类旁通" NOR,
                HIY "略有小成" NOR,
                HIY "心领神会" NOR,
                HIY "略有大成" NOR,
                MAG "已有大成" NOR,
                MAG "驾轻就熟" NOR,
                MAG "出类拔萃" NOR,
                MAG "初入佳境" NOR,
                RED "神乎其技" NOR,
                RED "出神入化" NOR,
                RED "豁然贯通" NOR,
                RED "超群绝伦" NOR,
                HIR "登峰造极" NOR,
                HIR "无可匹敌" NOR,
                HIR "卓然大家" NOR,
                HIR "一代宗师" NOR,
                HIR "神功盖世" NOR,
                HIC "举世无双" NOR,
                HIC "惊世骇俗" NOR,
                HIC "独步天下" NOR,
                HIC "空前绝后" NOR,
                HIC "旷古绝伦" NOR,
                HIG "登堂入室" NOR,
                HIG "超凡入圣" NOR,
                HIG "震古铄今" NOR,
                HIG "深藏不露" NOR,
                HIG "返璞归真" NOR,
                HIW "深不可测" NOR,
});

//////////////////// added by jingxue 12.5.2002
string *tough_level_desc = ({
        HIB "不堪一击" NOR,
        HIB "毫不足虑" NOR,
        HIB "不足挂齿" NOR,
        HIB "初学乍练" NOR,
        HIB "初窥门径" NOR,
        YEL "略知一二" NOR,
	YEL "普普通通" NOR,
	YEL "平平淡淡" NOR,
        YEL "平淡无奇" NOR,
        YEL "粗通皮毛" NOR,
        HIY "半生不熟" NOR,
        HIY "马马虎虎" NOR,
	HIY "略有小成" NOR,
        HIY "已有小成" NOR,
        HIY "鹤立鸡群" NOR,        
        MAG "驾轻就熟" NOR,
        MAG "心领神会" NOR,
        MAG "了然於胸" NOR,
	MAG "略有大成" NOR,
	MAG "已有大成" NOR,
	RED "青出于蓝" NOR,
	RED "挥洒自如" NOR,
        RED "豁然贯通" NOR,
        RED "出类拔萃" NOR,
        RED "超群绝伦" NOR,
	HIR "傲视群雄" NOR,
        HIR "神乎其技" NOR,
        HIR "威不可当" NOR,
        HIR "出神入化" NOR,
        HIR "非同凡响" NOR,
	HIC "无可匹敌" NOR,
	HIC "技冠群雄" NOR,
	HIC "卓然大家" NOR,
        HIC "登峰造极" NOR,
	HIC "所向披靡" NOR,
        HIG "一代宗师" NOR,
	HIG "神功盖世" NOR,
        HIG "举世无双" NOR,
        HIG "惊世骇俗" NOR,
        HIG "独步天下" NOR,
        HIW "超凡入圣" NOR,
        HIW "震古铄今" NOR,
	HIW "深藏不露" NOR,
	HIW "返璞归真" NOR,
        HIW "深不可测" NOR,

});

string gettof(object me, object ob)
{
	int p;
	if( !me || !ob || me==ob )
		return 0;
	p = ob->query_level()-me->query_level();
	
	if( p==0 )
		return MAG"旗鼓相当"NOR;
	//不如对方		
	if( p>0 )		
	{
		if( p>30 )	return HIW"深不可测"NOR;
		else if( p>20 ) return HIR"棋高一着"NOR;
		else if( p>10 ) return YEL"稍高一筹"NOR;
		else	return CYN"略高一筹"NOR;   
	}
	//对方不如
	else
	{
		p = -p;
		if( p>30 )	return CYN"不堪一击"NOR;
		else if( p>20 ) return YEL"远逊于你"NOR;
		else if( p>10 ) return HIR"稍低一筹"NOR;
		else	return HIC"略低一筹"NOR;
	}
}

string describe_dx(int value)
{
	value/= 1000;
	if( value<200 )
		return HIB "新入道途" NOR;
	else if( value<300 )
		return HIB "闻道则喜" NOR;
	else if( value<420 )
		return HIB "初领妙道" NOR;
	else if( value<560 )
		return HIB "略通道行" NOR;
	else if( value<720 )
		return HIB "渐入佳境" NOR;
	else if( value<2000 )
		return CYN "元神初具" NOR;
	else if( value<3300 )
		return CYN "道心稳固" NOR;
	else if( value<4800 )
		return CYN "一日千里" NOR;
	else if( value<6500 )
		return CYN "道高德隆" NOR;
	else if( value<8400 )
		return CYN "脱胎换骨" NOR;
	else if( value<15000 )
		return HIC "霞举飞升" NOR;
	else if( value<24000 )
		return HIC "道满根归" NOR;
	else if( value<27200 )
		return HIC "不堕轮回" NOR;
	else if( value<36000 )
		return HIC "已证大道" NOR;
	else if( value<95000 )
		return HIC "反璞归真" NOR; 
	else	return HIW "天人合一" NOR;
}

string dx_need()
{
	string str = "◇"+MUDLIB_NAME+"道行要求：  \n";
	str+= "  200年 "HIB "新入道途" NOR"        \n";
	str+= "  300年 "HIB "闻道则喜" NOR"        \n";
	str+= "  420年 "HIB "初领妙道" NOR"        \n";
	str+= "  560年 "HIB "略通道行" NOR"        \n";
	str+= "  720年 "HIB "渐入佳境" NOR"        \n";
	str+= "  900年 "CYN "元神初具" NOR"        \n";
	str+= " 2000年 "CYN "道心稳固" NOR"        \n";
	str+= " 3300年 "CYN "一日千里" NOR"        \n";
	str+= " 4800年 "CYN "道高德隆" NOR"        \n";
	str+= " 6500年 "CYN "脱胎换骨" NOR"        \n";
	str+= " 8400年 "HIC "霞举飞升" NOR"        \n";
	str+= "15000年 "HIC "道满根归" NOR"        \n";
	str+= "24000年 "HIC "不堕轮回" NOR"        \n";
	str+= "27200年 "HIC "已证大道" NOR"        \n";
	str+= "36000年 "HIC "反璞归真" NOR"        \n";
	str+= "95000年 "HIW "天人合一" NOR"        \n";
	return str;
}

string exp_need()
{
	string str;
	str = "◇"+MUDLIB_NAME+"等级要求：      \n";
	str+= "      1级 "HIB"初学乍练"NOR"       5级 "HIB"不知所以"NOR"\n";
	str+= "     10级 "HIB"粗通皮毛"NOR"      15级 "HIB"略识之无"NOR"\n";
	str+= "     40级 "HIB"渐有所悟"NOR"      45级 "YEL"半生不熟"NOR"\n";
	str+= "     50级 "YEL"马马虎虎"NOR"      55级 "YEL"触类旁通"NOR"\n";
	str+= "     60级 "HIY"略有小成"NOR"      65级 "HIY"心领神会"NOR"\n";
	str+= "     70级 "HIY"略有大成"NOR"      75级 "MAG"已有大成"NOR"\n";
	str+= "     80级 "MAG"驾轻就熟"NOR"      85级 "MAG"出类拔萃"NOR"\n";
	str+= "     90级 "MAG"初入佳境"NOR"      95级 "RED"神乎其技"NOR"\n";
	str+= "    100级 "RED"出神入化"NOR"     105级 "RED"豁然贯通"NOR"\n";
	str+= "    110级 "RED"超群绝伦"NOR"     115级 "HIR"登峰造极"NOR"\n";
	str+= "    120级 "HIR"无可匹敌"NOR"     125级 "HIR"卓然大家"NOR"\n";
	str+= "    130级 "HIR"一代宗师"NOR"     135级 "HIR"神功盖世"NOR"\n";
	str+= "    140级 "HIC"举世无双"NOR"     145级 "HIC"惊世骇俗"NOR"\n";
	str+= "    150级 "HIC"独步天下"NOR"     155级 "HIC"空前绝后"NOR"\n";
	str+= "    160级 "HIC"旷古绝伦"NOR"     165级 "HIG"登堂入室"NOR"\n";
	str+= "    170级 "HIG"超凡入圣"NOR"     175级 "HIG"震古铄今"NOR"\n";
	str+= "    180级 "HIG"深藏不露"NOR"     185级 "HIG"返璞归真"NOR"\n";
	str+= "    190级 "HIW"深不可测"NOR"\n";		
	return str;
}

string describe_exp(int value)
{
        int lvl;
	if( value<40 )
	{
		if( value<5 )	return HIB "初学乍练" NOR;
		else if( value<10 )	return HIB "不知所以" NOR;  	
		else if( value<20 )	return HIB "粗通皮毛" NOR;
		else	return HIB "略识之无" NOR;
	}
	lvl = value/5-4;
        if( lvl>=sizeof(exp_level_desc) ) 
        	lvl=sizeof(exp_level_desc)-1;
        return exp_level_desc[lvl];
}

string describe_neili(int value)
{
        int year, sixty, left;
        string line;
        
        year = value/100;
        sixty = year/60;
        left = year - sixty*60;

        if( year <= 0 )
        {
                line = HIB "不到一年" NOR;
                return line;
        }
        
        if(sixty > 0 )
        {
                if( left != 0 )
                { 
                        line = HIW + chinese_number(sixty) + "甲子" + NOR + "又" +  HIR + chinese_number(left) + "年" + NOR;
                }
                else 
                {
                        line = HIW + chinese_number(sixty) + "甲子"  + NOR;     
                }               
        }
        else	line = HIR + chinese_number(year)+"年" + NOR;
        return line;
}

string describe_fali(int value)
{
	if( value>=28500 )
		return HIW "法力无边" NOR;
	else if( value>=27000 )
		return HIC "变换莫测" NOR;
	else if( value>=25500 )
		return HIC "随心所欲" NOR;
	else if( value>=24000 )
		return HIC "包罗万象" NOR;
	else if( value>=22500 )
		return CYN "移星换斗" NOR;
	else if( value>=21000 )
		return CYN "负海担山" NOR;
	else if( value>=19500 )
		return CYN "呼风唤雨" NOR;
	else if( value>=18000 )
		return CYN "妙领天机" NOR;
	else if( value>=16500 )
		return CYN "预知祸福" NOR;
	else if( value>=15000 )
		return YEL "神出鬼没" NOR;
	else if( value>=13500 )
		return YEL "御剑飞行" NOR;
	else if( value>=12000 )
		return YEL "化身千万" NOR;
	else if( value>=10500 )
		return YEL "日行千里" NOR;
	else if( value>=9000 )
		return HIB "腾云驾雾" NOR;
	else if( value>=7500 )
		return HIB "降龙伏虎" NOR;
	else if( value>=6000 )
		return HIB "略晓变化" NOR;
	else	return HIB "初具法力" NOR; 
}

string query_description(int type)
{
    	int i,p;
	string *level_desc;
	string line = "";
	if(type==0) level_desc = dx_level_desc;
	else if(type==1) level_desc = exp_level_desc;
	else if(type==2) level_desc = fali_level_desc;
	else level_desc = tough_level_desc;
    	for(i=0; i<sizeof(level_desc); i++)
    	{
        	line += level_desc[i] + "    ";
        	if( (i%5)==4 ) line += "\n";
    	}
    	return line;
}

string _query_rank(object ob);

string query_rank(object ob)
{
    	string rank=_query_rank(ob);
    	string s1,s2,s3;
    	int len, len1, len2;
    
    	if(sscanf(rank,"%s(%s)%s",s1,s2,s3)!=3) 
    		return rank;
    	rank = replace_string(rank, "(", "【");
    	rank = replace_string(rank, ")", "】");
    	len=14-sizeof(s2);
    	if(len<1) return rank;

    	len1=len/2;
    	len2=len-len1;
    	if(len1) s2=repeat_string(" ",len1)+s2;
    	if(len2) s2+=repeat_string(" ",len2);
    	return s1+"【"+s2+"】"+s3;
}

string _query_rank(object ob)
{
	string str,at;
	int girl,lvl;

	if( ob->is_ghost() ) 
		return HIB "【 鬼  魂 】" NOR;
	if( !stringp(at = ob->query("added_title")) )
		at = "无名";
	lvl = ob->query_level();
	if( ob->query("gender")=="女性" )
		girl = 1;
	else	girl = 0;		
		
	if( wizhood(ob)!="(player)" )
	{
		switch(wizhood(ob)) 
		{
			case "(admin)" : return sprintf(HIW "【"+at+"巫%s】" NOR,girl>0?"女":"师");
			case "(arch)"  : return sprintf(HIR "【"+at+"巫%s】" NOR,girl>0?"女":"师");
			case "(wizard)": return sprintf(HIM "【"+at+"巫%s】" NOR,girl>0?"女":"师");
			case "(apprentice)": return sprintf(HIC "【见习巫%s】" NOR,girl>0?"女":"师");
			case "(immortal)": return sprintf(HIG "【客座巫%s】" NOR,girl>0?"女":"师");
			default : return GRN "【荣誉玩家】" NOR;	
		}
	}	
	str = FAMILY_D->query_rank(ob);
	str = NOR"【"HIG+str+NOR"】";
	if( strsrch(str,"%s")!=-1 )
		str = replace_string(str,"%s",at);
	return str;	
}

string query_self(object ob)
{
        int age;
        string str;

        if( stringp(str = ob->query("rank_info/self")) )
                return str;

        // added by snowcat
        age = ob->query("fake_age");
        if(age == 0) age = ob->query("age");
        switch(ob->query("gender")) 
        {
                case "女性":
                        switch(ob->query("class")) 
                        {
				case "bonze":
        				if( age < 50 ) return "贫尼";
        				else return "老尼";
        				break;
				default:
        				if( age < 30 ) return "小女子";
        				else return "妾身";
        				break;
                        }
                default:
                        switch(ob->query("class")) 
                        {
				case "bonze":
        				if( age < 50 ) return "贫僧";
        				else return "老纳";
        				break;
				case "taoist":
        				return "贫道";
        				break;
				case "scholar":
        				if( age < 30 ) return "晚生";
        				else return "不才";
        				break;
				default:
        				if( age < 50 ) return "在下";
        				else return "老头子";
        				break;
                        }
	}
}

string query_respect(object ob)
{
        int lvl,age,gender;
        string str,cls;

        if( stringp(str = ob->query("rank_info/respect")) )
                return str;
	if( ob->query("race")!="人类" )
		return ob->name();
	lvl = ob->query_level();
	age = ob->query("fake_age");
	if( age<=0 )
		age = ob->query("age");
	if( ob->query("gender")=="女性" )
		gender = 0;
	else	gender = 1;			
	cls = ob->query("class");
	if( !cls )
		cls = "";		
	switch(cls)
	{
		case "xian":
		case "shen":
			if( lvl>=180 )
				return ({"娘娘","圣人",})[gender];
			else if( lvl>=150 )
				return ({"仙子","上仙",})[gender];
			else if( lvl>=90 )
				return ({"仙女","大仙",})[gender];
			else if( lvl>=40 )
			{
				if( age<18 )
					return ({"玉女","金童",})[gender];
				else	return ({"仙姑","神仙",})[gender];
			}
			else
			{
				if( age<18 )
					return ({"小姑娘","小兄弟",})[gender];
				else if( age<25 )
					return ({"姑娘","壮士",})[gender];
				else if( age<50 )
					return ({"女侠","大侠",})[gender];
				else	return ({"婆婆","老爷子",})[gender];
			}
		case "yaomo":
			if( lvl>=180 )
				return ({"圣母","老祖",})[gender];
			else if( lvl>=150 )
				return ({"女大圣","大圣",})[gender];
			else if( lvl>=90 )
			{
				if( age<18 )	
					return ({"小圣女","小圣子",})[gender];
				else	return ({"圣女","圣子",})[gender];
			}
			else if( lvl>=40 )
			{
				if( age<18 )
					return ({"小公主","小神仙",})[gender];
				else	return ({"公主","大仙",})[gender];
			}
			else
			{
				if( age<18 )
					return ({"小姑娘","小兄弟",})[gender];
				else if( age<25 )
					return ({"姑娘","壮士",})[gender];
				else if( age<50 )
					return ({"女侠","大侠",})[gender];
				else	return ({"婆婆","老爷子",})[gender];
			}
		case "bonze" :
			if( lvl>=180 )
				return "老佛爷";
			else if( lvl>=150 )
			{
				if( age<18 )	
					return "小菩萨";
				else	return "菩萨";
			}
			else if( lvl>=90 )
			{
				if( age<18 )	
					return "小长老";
				else	return ({"女长老","长老",})[gender];
			}
			else if( lvl>=40 )
			{
				if( age<18 )
					return ({"小师太","小师傅",})[gender];
				else	return ({"师太","大师",})[gender];
			}
			else
			{
				if( age<18 )
					return ({"小尼姑","小和尚",})[gender];
				else	return ({"女师傅","大和尚",})[gender];
			}	
		case "taoist" :			
			if( lvl>=180 )
				return ({"娘娘","圣人",})[gender];
			else if( lvl>=150 )
				return "天尊";
			else if( lvl>=90 )
			{
				if( age<18 )	
					return ({"小玄女","小真人",})[gender];
				else	return ({"玄女","真人",})[gender];
			}
			else if( lvl>=40 )
			{
				if( age<18 )
					return "小天师";
				else	return "天师";
			}
			else
			{
				if( age<18 )
					return ({"女道童","小道童",})[gender];
				else	return ({"女道长","道长",})[gender];
			}
		case "dragon" :
			if( lvl>=180 )
				return ({"娘娘","神王",})[gender];
			else if( lvl>=150 )
				return ({"龙神","龙王",})[gender];
			else if( lvl>=90 )
			{
				if( age<18 )	
					return ({"小龙女","小太子",})[gender];
				else	return ({"龙女","龙太子",})[gender];
			}
			else if( lvl>=40 )
			{
				if( age<18 )
					return "小海使";
				else	return "海使";
			}
			else
			{
				if( age<18 )
					return ({"小姑娘","小兄弟",})[gender];
				else if( age<25 )
					return ({"姑娘","壮士",})[gender];
				else if( age<50 )
					return ({"女侠","大侠",})[gender];
				else	return ({"婆婆","老爷子",})[gender];
			}
		case "fighter" :
			if( lvl>=180 )
				return ({"娘娘","圣人",})[gender];
			else if( lvl>=150 )
			{
				if( age<18 )	
					return "小元帅";
				else	return ({"女元帅","元帅",})[gender];
			}
			else if( lvl>=90 )
			{
				if( age<18 )	
					return "小将军";
				else	return ({"女将军","将军",})[gender];
			}
			else if( lvl>=40 )
			{
				if( age<18 )
					return "小将军";
				else	return ({"女将军","军爷",})[gender];
			}
			else
			{
				if( age<18 )
					return ({"小姑娘","小兄弟",})[gender];
				else if( age<25 )
					return ({"姑娘","壮士",})[gender];
				else if( age<50 )
					return ({"女侠","大侠",})[gender];
				else	return ({"婆婆","老爷子",})[gender];
			}
		case "youling":	
		case "ghost":
			if( lvl>=180 )
				return ({"娘娘","圣人",})[gender];
			else if( lvl>=150 )
			{
				if( age<18 )	
					return ({"小郡主","小王爷",})[gender];
				else	return ({"女王","鬼王",})[gender];
			}
			else if( lvl>=90 )
			{
				if( age<18 )	
					return "小无常";
				else	return ({"勾魂奶奶","无常爷爷",})[gender];
			}
			else if( lvl>=40 )
			{
				if( age<18 )
					return "小魂使";
				else	return "魂使";
			}
			else
			{
				if( age<18 )
					return ({"小姑娘","小兄弟",})[gender];
				else if( age<25 )
					return ({"姑娘","壮士",})[gender];
				else if( age<50 )
					return ({"女侠","大侠",})[gender];
				else	return ({"婆婆","老爷子",})[gender];
			}
		case "dancer" :	
				if( age<18 )
					return "小姑娘";
				else	return "女才人";
		default :	
			if( lvl>=180 )
				return ({"娘娘","圣人",})[gender];
			else if( lvl>=150 )
				return ({"仙子","上仙",})[gender];
			else if( lvl>=90 )
			{
				if( age<18 )	
					return ({"仙子","大仙",})[gender];
				else	return ({"女神仙","神仙",})[gender];
			}
			else if( lvl>=40 )
				return ({"仙姑","仙长",})[gender];
			else
			{
				if( age<18 )
					return ({"小姑娘","小兄弟",})[gender];
				else if( age<25 )
					return ({"姑娘","壮士",})[gender];
				else if( age<50 )
					return ({"女侠","大侠",})[gender];
				else	return ({"婆婆","老爷子",})[gender];		
			}
	}		
}

string query_rude(object ob)
{
        int age;
        string str;

        if( stringp(str = ob->query("rank_info/rude")) )
                return str;

        // added by snowcat
        age = ob->query("fake_age");
        if(age == 0) age = ob->query("age");
        switch(ob->query("gender")) 
        {
                case "女性":
                        switch(ob->query("class")) 
                        {
				case "yaomo":
        				if(age < 30) return "小妖女";
        				else if(age < 50) return "妖女";
        				else return "老妖婆";
        				break;
				case "bonze":
        				if(age < 30) return "小贼尼";
        				else if(age < 50) return "贼尼";
        				else return "老贼尼";
        				break;
				default:
        				if( age < 30 ) return "小贱人";
        				else if(age < 50) return "贱人";
        				else return "死老太婆";
        				break;
                        }
                default:
                        switch(ob->query("class")) 
                        {
				case "yaomo":
				        if( age < 50 ) return "死妖怪";
        				else return "老妖怪";
        				break;
				case "bonze":
        				if( age < 50 ) return "死秃驴";
        				else return "老秃驴";
        				break;
				case "taoist":
        				return "死牛鼻子";
        				break;
				case "scholar":
        				if( age < 18 ) return "小书呆子";
        				else if( age < 50 ) return "臭书呆子";
        				else return "老酸儒";
        				break;
				default:
        				if( age < 18 ) return "小王八蛋";
        				else if( age < 50 ) return "臭贼";
        				else return "老匹夫";
        				break;
			}
	}
}

string query_self_rude(object ob)
{
        int age;
        string str;

        if( stringp(str = ob->query("rank_info/self_rude")) )
                return str;

        // added by snowcat
        age = ob->query("fake_age");
        if(age == 0) age = ob->query("age");
        switch(ob->query("gender")) 
        {
                case "女性":
                        switch(ob->query("class")) 
                        {
				case "bonze":
        				if( age < 50 ) return "贫尼";
        				else return "老尼";
        				break;
				default:
        				if( age < 50 ) return "本姑娘";
        				else return "老娘";
        				break;
                        }
                default:
                        switch(ob->query("class")) 
                        {
				case "bonze":
        				if( age < 50 ) return "大和尚我";
        				else return "老和尚我";
        				break;
				case "taoist":
        				return "本山人";
        				break;
				case "scholar":
        				if( age < 50 ) return "本相公";
        				else return "老夫子我";
        				break;
				default:
        				if( age < 18 ) return "你家小爷我";
        				else if( age < 50 ) return "大爷我";
        				else return "你爷爷我";
        				break;
                        }
        }
}

string query_self_close(object ob)
{
	object who = this_player();
        int a1, a2;
	
	if( !who || ob==who )
		return "";
	a1 = who->query_level();
	a2 = ob->query_level();
	if( a1<a2 )
	{
		switch(ob->query("gender")) 
		{
			case "女性" : return "姐姐我";
			default : return "愚兄我";
		}		
	}
	else if( a1>a2 )
	{
		switch(ob->query("gender")) 
		{
			case "女性" : return "小妹我";
			default : return "小弟我";
		}		
	}
	else 
	{
		if(a2 = (int)ob->query("mud_age"))
                        a1 = who->query("mud_age");
                else
                {
                        a1 = who->query("age");
                        a2 = ob->query("age");
                }
	        switch(ob->query("gender")) 
	        {
        		case "女性" :
                		if(a1 >= a2)
                        		return "姐姐我";
                		else	return "小妹我";
			default :
                		if(a1 >= a2)
                        		return "愚兄我";
                		else	return "小弟我";
        	}
        }	
}

string query_close(object ob)
{
	object who = this_player();
        int a1, a2;
	
	if( !who || ob==who )
		return "";
	a1 = ob->query_level();
	a2 = who->query_level();
	if( a1>a2 )
	{
		switch(ob->query("gender")) 
		{
			case "女性" : return "姐姐";
			default : return "兄长";
		}		
	}
	else if( a1<a2 )
	{
		switch(ob->query("gender")) 
		{
			case "女性" : return "妹妹";
			default : return "弟弟";
		}		
	}
	else 
	{
		if(a2 = (int)who->query("mud_age"))
                        a1 = ob->query("mud_age");
                else
                {
                        a1 = ob->query("age");
                        a2 = who->query("age");
                }
	        switch(ob->query("gender")) 
	        {
        		case "女性" :
                		if(a1 >= a2)
                        		return "姐姐";
                		else	return "妹妹";
			default :
                		if(a1 >= a2)
                        		return "兄长";
                		else	return "弟弟";
        	}
        }	
}