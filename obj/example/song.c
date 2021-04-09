// An example song
// /obj/example/song.c

// 此文件禁止随意移动和更改
// /obj/example/song.c
// 配合 /cmds/std/song.c 运作
// 利用本物件来写一些必备函数,
// 也用来存歌曲资料. wade 7/7/1996
// Last modified by waiwai@2003/01/20
// Last Modified by Jingxue for XYCQ 4.10.2004

#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

mapping songs;
nosave object who_play;
nosave string play_what;

void get_mail_text(mapping mail, string str);

void create()
{
	set_name ("点唱金榜", ({ "song menu", "menu" }) );
	set("long", "你只有用 song 命令才处理点唱金榜\n");
	set("unit", "本");
	set("no_drop", 1);
	set("no_sell",1);
	set("deadfly", 1);
	set("no_put", 1);
	set("no_insert", 1);
//	set("channels":({"chat","music",}));
	this_object()->restore();
	setup();
}

string query_save_file()
{
	return DATA_DIR + "song";
}

void add_song (string name, object who, string songer, string cont)
{
  	string *names; 

  	if (!songs) songs = ([]);
  	if (!name || !who || !songer || !cont) return;

  	songs[name] = ([
    		"歌名"		: name,
    		"原唱者"	: songer,
		//"纪录者"	: who->query ("id"),
    		"纪录者"	: log_id(who),
    		"内容"	 	: cont,
		//"时间"	: ctime (time()),
    		"时间"		: log_time(),
    		"使用次数"	: 0
  ]);
  this_object()->save();
}

int query_exist (string name, object who)
{
  	if (!songs) return 0;
  		else if (mapp (songs[name]) && songs[name]["纪录者"] != log_id(who))

		//  else if (mapp (songs[name]) && songs[name]["纪录者"] != who->query ("id"))
    	return 1;
  	return 0;
}

varargs mixed query_songs(string name)
{
  	if (!songs || songs == ([])) return 0;

  	if (!name)
    		return keys (songs);
  	else
    		return songs[name];
}

void delete_song(string name, object who)
{
  	if (!songs || songs == ([])) return;

  	if (wizardp (who) ||
//      mapp (songs[name]) && songs[name]["纪录者"] == who->query ("id"))
      	mapp (songs[name]) && songs[name]["纪录者"] == log_id(who)) {
      	map_delete (songs, name);
  	}

  	this_object()->save();
}

int query_playing ()
{
  	return who_play != 0;
}

int play (string name, object who, object target)
{
  	string *cont, *str, tmp, tmp1;
  	int	 i, j, n, delay;

  	if (!songs || songs == ([])) return 0;
	
  	if (!mapp (songs[name])) return 0;

  	if (objectp (who_play)) return 0;
  	who_play = who;
  	play_what = name;

  	str = ({});
  	tmp = songs[name]["内容"]; 
  	cont = explode (tmp, "\n");

  	for (i=0; i<sizeof (cont); i++) {
    	if (cont[i] != "" && sscanf (cont[i], "%s %s", tmp1, tmp) == 0) {
      	tmp1 = cont[i];
      	n = 1;
      	for (j=0; j<strlen (tmp1); j++)
        if (tmp1[j] > '9' || tmp1[j] < '0') {
          	n = 0;
          	break;
        }
      	if (n) {
        	i++;
        	if (i < sizeof (cont))
          	str += ({ tmp1 + " " + cont[i] });
      	}
      	else
        str += ({ "3 " + cont[i] });
    	}
    	else
      	str += ({ "3 " + cont[i] });
  	}

  	if (sizeof (str) == 0) return 0;

  	set_name (who->name(), ({ who->query ("id") }) );
  	songs[name]["使用次数"]++;
  	this_object()->save();
	if (!target)
  		CHANNEL_D->do_channel (this_object(), "chat","各位，请欣赏(music频道)本人为各位点播的："HIR"["+play_what+"]"NOR);
	else
  		CHANNEL_D->do_channel (this_object(), "chat","各位，请欣赏(music频道)本人为"HIG+(string)target->query("name")+HIC"点播的："HIR"["+play_what+"]"NOR);
  	if (sscanf (str[0], "%d %s", delay, tmp) == 2) {
    	call_out ("play_it", delay+3, tmp, str[1..<1]);
  	}
  	else {
    	call_out ("play_stop", 5);
  	}

  	return 1;
}

void play_it (string what, string *str)
{
  	string tmp;
  	int	 delay;

  	CHANNEL_D->do_channel (this_object(), "music",  what);

  	if (sizeof (str) > 0 && sscanf (str[0], "%d %s", delay, tmp) == 2) {
    	call_out ("play_it", delay, tmp, str[1..<1]);
  	}
  	else {
    	call_out ("play_stop", 5);
  	} 
}

void play_stop ()
{
  	play_what = 0;
  	who_play = 0;
  	CHANNEL_D->do_channel (this_object(), "music", HIY"谢谢各位，请掌声(chat* applaud)鼓励鼓励！"NOR);
  	set_name ("点唱金榜", ({ "song menu", "menu" }) );

  	destruct (this_object());
}

string *query_top (int type, string nm)
{
  	string	*k;
  	mapping	*ss;
  	mapping	*s;
  	int i, n, l, r;

  	if (!songs || songs == ([])) return 0;
  	if (!nm)
      	n = 10;
  	else if (sscanf (nm, "%d", n) != 1)
    	n = 4;
  	else if (n < 4) n = 4;

  	k = keys (songs);

  	if (sizeof (songs) <= n)
    		return k;

  	ss = ({});
  	for (i=0; i<sizeof (k); i++)
    	ss += ({ songs[k[i]] });

  	if (type == 1)
    	s = sort_array (ss, "sort_times", this_object()); 
  	else if (type == 2)
    	s = sort_array (ss, "sort_names", this_object());
  	else
    	s = sort_array (ss, "sort_source", this_object());

  	k = ({});
  	if (type == 1)	// 照使用次数排
    	for (i=0; i<n; i++)
      	k += ({ sprintf (HIG"%25s"NOR"%19s/%18s"HIW"%4d "NOR"[%s]",
		s[i]["歌名"],
		s[i]["原唱者"],
		s[i]["纪录者"],
                s[i]["使用次数"],
                s[i]["时间"]) });
  	if (type == 2) {	// 照歌名长度排
    	if (!nm) {					// song -n
      	for (i=0; i<sizeof (s); i++)
      	k += ({ sprintf (HIG"%25s"NOR"%19s/%18s"HIW"%4d "NOR"[%s]",
		s[i]["歌名"],
		s[i]["原唱者"],
		s[i]["纪录者"],
                s[i]["使用次数"],
                s[i]["时间"]) });
    	}
    	else if (nm[<1] == '+') {			// song -n N+
      	for (i=0; i<sizeof (s); i++)
        if (strlen (s[i]["歌名"]) >= n)
      	k += ({ sprintf (HIG"%25s"NOR"%19s/%18s"HIW"%4d "NOR"[%s]",
		s[i]["歌名"],
		s[i]["原唱者"],
		s[i]["纪录者"],
                s[i]["使用次数"],
                s[i]["时间"]) });
    	}
    	else if (nm[<1] == '-') {			// song -n N-
      	for (i=0; i<sizeof (s); i++)
        if (strlen (s[i]["歌名"]) <= n)
      	k += ({ sprintf (HIG"%25s"NOR"%19s/%18s"HIW"%4d "NOR"[%s]",
		s[i]["歌名"],
		s[i]["原唱者"],
		s[i]["纪录者"],
                s[i]["使用次数"],
                s[i]["时间"]) });
    	}
    	else if (sscanf (nm, "%d-%d", l, r) == 2) {	// song -n M-N
      	for (i=0; i<sizeof (s); i++)
        if (strlen (s[i]["歌名"]) >= l && strlen (s[i]["歌名"]) <= r)
      	k += ({ sprintf (HIG"%25s"NOR"%19s/%18s"HIW"%4d "NOR"[%s]",
		s[i]["歌名"],
		s[i]["原唱者"],
		s[i]["纪录者"],
                s[i]["使用次数"],
                s[i]["时间"]) });
    	}
    	else					// song -n N
      	for (i=0; i<sizeof (s); i++)
        if (strlen (s[i]["歌名"]) >= n-1 && strlen (s[i]["歌名"]) <= n+1)
      	k += ({ sprintf (HIG"%25s"NOR"%19s/%18s"HIW"%4d "NOR"[%s]",
		s[i]["歌名"],
		s[i]["原唱者"],
		s[i]["纪录者"],
                s[i]["使用次数"],
                s[i]["时间"]) });
  	}
  	else if (type == 3) {	// 照原唱者排
    	if (nm) {					// song -a WHO
      	for (i=0; i<sizeof (s); i++)
        if (s[i]["原唱者"] == nm)
      	k += ({ sprintf (HIG"%25s"NOR"%19s/%18s"HIW"%4d "NOR"[%s]",
		s[i]["歌名"],
		s[i]["原唱者"],
		s[i]["纪录者"],
                s[i]["使用次数"],
                s[i]["时间"]) });
    	}
    	else {					// song -a
      	for (i=0; i<sizeof (s); i++)
      	k += ({ sprintf (HIG"%25s"NOR"%19s/%18s"HIW"%4d "NOR"[%s]",
		s[i]["歌名"],
		s[i]["原唱者"],
		s[i]["纪录者"],
                s[i]["使用次数"],
                s[i]["时间"]) });
    	}
  	}
  	else if (type == 4) {	// 搜寻歌曲含有 nm 字串的清单.
    	for (i=0; i<sizeof (s); i++)
      	if (strsrch (s[i]["歌名"], nm) != -1)
      	k += ({ sprintf (HIG"%25s"NOR"%19s/%18s"HIW"%4d "NOR"[%s]",
		s[i]["歌名"],
		s[i]["原唱者"],
		s[i]["纪录者"],
                s[i]["使用次数"],
                s[i]["时间"]) });
  	}

  	if (!who_play)
    	destruct (this_object());
  	return k;
}

int sort_times (mapping m1, mapping m2)
{
  	return m2["使用次数"] - m1["使用次数"];
}

int sort_names (mapping m1, mapping m2)
{
  	return strlen (m1["歌名"]) - strlen (m2["歌名"]);
}

int sort_source (mapping m1, mapping m2)
{
  	return strcmp (m1["原唱者"], m2["原唱者"]);
}

int song_number()
{
  	return sizeof (songs);
}

void adjust()
{
  	int i;
  	string *song, s;

  	song = keys (songs);
  	s = song[0];
  	for (i=0; i<sizeof (songs); i++)
    	if (songs[song[i]]["使用次数"] < songs[s]["使用次数"])
      	s = song[i];

  	map_delete (songs, s);
}
