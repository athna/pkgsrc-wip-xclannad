$NetBSD$

- don't assume signed char for arm and powerpc

--- scn2k/scn2k_text.cc.orig	2008-08-31 15:26:43.000000000 +0000
+++ scn2k/scn2k_text.cc
@@ -789,7 +789,7 @@ void TextImpl::AddText(const char* str_o
 	/* ＊ = 81 96 A-Z = 0x82 [0x60-0x79] */
 	/* ％ = 81 93 A-Z = 0x82 [0x60-0x79] */
 	for (i=0; cnt<10000 && str_o[i] != 0; i++) {
-		if (str_o[i] < 0) {
+		if ((str_o[i] & 0x80) != 0) {
 			if ( (unsigned char)str_o[i] == 0x81 && (unsigned char)str_o[i+1] == 0x96 && (unsigned char)str_o[i+2] == 0x82) {
 				int c = str_o[i+3];
 				if (c >= 0x60 && c <= 0x79 && replace_name[c-0x60].length() != 0) { // 名前変換
@@ -831,7 +831,7 @@ void TextImpl::AddText(const char* str_o
 					text_stream.AddName(name_top);
 					break;
 				}
-				if (*s < 0 && s[1] != 0) s++; // 全角文字なら２字飛ばす
+				if ((*s & 0x80) != 0 && s[1] != 0) s++; // 全角文字なら２字飛ばす
 			}
 			str_top = s;
 		}
@@ -840,7 +840,7 @@ void TextImpl::AddText(const char* str_o
 			text_stream.Add(str_top);
 			text_stream.AddReturn();
 			str_top = s;
-		} else if (*s < 0 && s[1] != 0) s++;
+		} else if ((*s & 0x80) != 0 && s[1] != 0) s++;
 	}
 	text_stream.Add(str_top);
 	return;
