//void eeprom_clear(int begin_,int end_){
//
//
//     for (int i = begin_; i < end_; ++i)
//        {
//         EEPROM.write(i, 0);
//         
//         }
//
//         Serial.println("eeprom was cleared");
//  
//}
//
//String read_eeprom(int begin_,int end_){
//   String text_eeprom = "";
//   for (int i = begin_; i < end_; ++i)
//    {
//      char abj = char(EEPROM.read(i));
//      if(abj>0){
//        text_eeprom += abj;
//      }
//    }
//  return text_eeprom;
//}
//
//void write_eeprom(int begin_,String text_eeprom){
//  
//   for (int i = 0; i < text_eeprom.length(); ++i)
//    {
//      EEPROM.write(begin_+i, text_eeprom[i]);
//    }
//
//    EEPROM.commit();
//    Serial.print("Write eeprom :");
//    Serial.println(text_eeprom);
// 
//}
//
//String url_encode(String urlChars)
//{
//
//  
//  
//
//  urlChars.replace("GET /action_page.php?", "");
//  urlChars.replace("password=","");
//  urlChars.replace(" HTTP/1.1","");
//  urlChars.replace("%0D%0A", String('\n'));
//
//  urlChars.replace("+",   " ");
//  urlChars.replace("%20", " ");
//  urlChars.replace("%21", "!");
//  urlChars.replace("%22", String(char('\"')));
//  urlChars.replace("%23", "#");
//  urlChars.replace("%24", "$");
//  urlChars.replace("%25", "%");
//  urlChars.replace("%26", "&");
//  urlChars.replace("%27", String(char(39)));
//  urlChars.replace("%28", "(");
//  urlChars.replace("%29", ")");
//  urlChars.replace("%2A", "*");
//  urlChars.replace("%2B", "+");
//  urlChars.replace("%2C", ",");
//  urlChars.replace("%2D", "-");
//  urlChars.replace("%2E", ".");
//  urlChars.replace("%2F", "/");
//  urlChars.replace("%30", "0");
//  urlChars.replace("%31", "1");
//  urlChars.replace("%32", "2");
//  urlChars.replace("%33", "3");
//  urlChars.replace("%34", "4");
//  urlChars.replace("%35", "5");
//  urlChars.replace("%36", "6");
//  urlChars.replace("%37", "7");
//  urlChars.replace("%38", "8");
//  urlChars.replace("%39", "9");
//  urlChars.replace("%3A", ":");
//  urlChars.replace("%3B", ";");
//  urlChars.replace("%3C", "<");
//  urlChars.replace("%3D", "=");
//  urlChars.replace("%3E", ">");
//  urlChars.replace("%3F", "?");
//  urlChars.replace("%40", "@");
//  urlChars.replace("%41", "A");
//  urlChars.replace("%42", "B");
//  urlChars.replace("%43", "C");
//  urlChars.replace("%44", "D");
//  urlChars.replace("%45", "E");
//  urlChars.replace("%46", "F");
//  urlChars.replace("%47", "G");
//  urlChars.replace("%48", "H");
//  urlChars.replace("%49", "I");
//  urlChars.replace("%4A", "J");
//  urlChars.replace("%4B", "K");
//  urlChars.replace("%4C", "L");
//  urlChars.replace("%4D", "M");
//  urlChars.replace("%4E", "N");
//  urlChars.replace("%4F", "O");
//  urlChars.replace("%50", "P");
//  urlChars.replace("%51", "Q");
//  urlChars.replace("%52", "R");
//  urlChars.replace("%53", "S");
//  urlChars.replace("%54", "T");
//  urlChars.replace("%55", "U");
//  urlChars.replace("%56", "V");
//  urlChars.replace("%57", "W");
//  urlChars.replace("%58", "X");
//  urlChars.replace("%59", "Y");
//  urlChars.replace("%5A", "Z");
//  urlChars.replace("%5B", "[");
//  urlChars.replace("%5C", String(char(65)));
//  urlChars.replace("%5D", "]");
//  urlChars.replace("%5E", "^");
//  urlChars.replace("%5F", "_");
//  urlChars.replace("%60", "`");
//  urlChars.replace("%61", "a");
//  urlChars.replace("%62", "b");
//  urlChars.replace("%63", "c");
//  urlChars.replace("%64", "d");
//  urlChars.replace("%65", "e");
//  urlChars.replace("%66", "f");
//  urlChars.replace("%67", "g");
//  urlChars.replace("%68", "h");
//  urlChars.replace("%69", "i");
//  urlChars.replace("%6A", "j");
//  urlChars.replace("%6B", "k");
//  urlChars.replace("%6C", "l");
//  urlChars.replace("%6D", "m");
//  urlChars.replace("%6E", "n");
//  urlChars.replace("%6F", "o");
//  urlChars.replace("%70", "p");
//  urlChars.replace("%71", "q");
//  urlChars.replace("%72", "r");
//  urlChars.replace("%73", "s");
//  urlChars.replace("%74", "t");
//  urlChars.replace("%75", "u");
//  urlChars.replace("%76", "v");
//  urlChars.replace("%77", "w");
//  urlChars.replace("%78", "x");
//  urlChars.replace("%79", "y");
//  urlChars.replace("%7A", "z");
//  urlChars.replace("%7B", String(char(123)));
//  urlChars.replace("%7C", "|");
//  urlChars.replace("%7D", String(char(125)));
//  urlChars.replace("%7E", "~");
//  urlChars.replace("%7F", "Â");
//  urlChars.replace("%80", "`");
//  urlChars.replace("%81", "Â");
//  urlChars.replace("%82", "â");
//  urlChars.replace("%83", "Æ");
//  urlChars.replace("%84", "â");
//  urlChars.replace("%85", "â¦");
//  urlChars.replace("%86", "â");
//  urlChars.replace("%87", "â¡");
//  urlChars.replace("%88", "Ë");
//  urlChars.replace("%89", "â°");
//  urlChars.replace("%8A", "Å");
//  urlChars.replace("%8B", "â¹");
//  urlChars.replace("%8C", "Å");
//  urlChars.replace("%8D", "Â");
//  urlChars.replace("%8E", "Å½");
//  urlChars.replace("%8F", "Â");
//  urlChars.replace("%90", "Â");
//  urlChars.replace("%91", "â");
//  urlChars.replace("%92", "â");
//  urlChars.replace("%93", "â");
//  urlChars.replace("%94", "â");
//  urlChars.replace("%95", "â¢");
//  urlChars.replace("%96", "â");
//  urlChars.replace("%97", "â");
//  urlChars.replace("%98", "Ë");
//  urlChars.replace("%99", "â¢");
//  urlChars.replace("%9A", "Å¡");
//  urlChars.replace("%9B", "âº");
//  urlChars.replace("%9C", "Å");
//  urlChars.replace("%9D", "Â");
//  urlChars.replace("%9E", "Å¾");
//  urlChars.replace("%9F", "Å¸");
//  urlChars.replace("%A0", "Â");
//  urlChars.replace("%A1", "Â¡");
//  urlChars.replace("%A2", "Â¢");
//  urlChars.replace("%A3", "Â£");
//  urlChars.replace("%A4", "Â¤");
//  urlChars.replace("%A5", "Â¥");
//  urlChars.replace("%A6", "Â¦");
//  urlChars.replace("%A7", "Â§");
//  urlChars.replace("%A8", "Â¨");
//  urlChars.replace("%A9", "Â©");
//  urlChars.replace("%AA", "Âª");
//  urlChars.replace("%AB", "Â«");
//  urlChars.replace("%AC", "Â¬");
//  urlChars.replace("%AE", "Â®");
//  urlChars.replace("%AF", "Â¯");
//  urlChars.replace("%B0", "Â°");
//  urlChars.replace("%B1", "Â±");
//  urlChars.replace("%B2", "Â²");
//  urlChars.replace("%B3", "Â³");
//  urlChars.replace("%B4", "Â´");
//  urlChars.replace("%B5", "Âµ");
//  urlChars.replace("%B6", "Â¶");
//  urlChars.replace("%B7", "Â·");
//  urlChars.replace("%B8", "Â¸");
//  urlChars.replace("%B9", "Â¹");
//  urlChars.replace("%BA", "Âº");
//  urlChars.replace("%BB", "Â»");
//  urlChars.replace("%BC", "Â¼");
//  urlChars.replace("%BD", "Â½");
//  urlChars.replace("%BE", "Â¾");
//  urlChars.replace("%BF", "Â¿");
//  urlChars.replace("%C0", "Ã");
//  urlChars.replace("%C1", "Ã");
//  urlChars.replace("%C2", "Ã");
//  urlChars.replace("%C3", "Ã");
//  urlChars.replace("%C4", "Ã");
//  urlChars.replace("%C5", "Ã");
//  urlChars.replace("%C6", "Ã");
//  urlChars.replace("%C7", "Ã");
//  urlChars.replace("%C8", "Ã");
//  urlChars.replace("%C9", "Ã");
//  urlChars.replace("%CA", "Ã");
//  urlChars.replace("%CB", "Ã");
//  urlChars.replace("%CC", "Ã");
//  urlChars.replace("%CD", "Ã");
//  urlChars.replace("%CE", "Ã");
//  urlChars.replace("%CF", "Ã");
//  urlChars.replace("%D0", "Ã");
//  urlChars.replace("%D1", "Ã");
//  urlChars.replace("%D2", "Ã");
//  urlChars.replace("%D3", "Ã");
//  urlChars.replace("%D4", "Ã");
//  urlChars.replace("%D5", "Ã");
//  urlChars.replace("%D6", "Ã");
//  urlChars.replace("%D7", "Ã");
//  urlChars.replace("%D8", "Ã");
//  urlChars.replace("%D9", "Ã");
//  urlChars.replace("%DA", "Ã");
//  urlChars.replace("%DB", "Ã");
//  urlChars.replace("%DC", "Ã");
//  urlChars.replace("%DD", "Ã");
//  urlChars.replace("%DE", "Ã");
//  urlChars.replace("%DF", "Ã");
//  urlChars.replace("%E0", "Ã");
//  urlChars.replace("%E1", "Ã¡");
//  urlChars.replace("%E2", "Ã¢");
//  urlChars.replace("%E3", "Ã£");
//  urlChars.replace("%E4", "Ã¤");
//  urlChars.replace("%E5", "Ã¥");
//  urlChars.replace("%E6", "Ã¦");
//  urlChars.replace("%E7", "Ã§");
//  urlChars.replace("%E8", "Ã¨");
//  urlChars.replace("%E9", "Ã©");
//  urlChars.replace("%EA", "Ãª");
//  urlChars.replace("%EB", "Ã«");
//  urlChars.replace("%EC", "Ã¬");
//  urlChars.replace("%ED", "Ã­");
//  urlChars.replace("%EE", "Ã®");
//  urlChars.replace("%EF", "Ã¯");
//  urlChars.replace("%F0", "Ã°");
//  urlChars.replace("%F1", "Ã±");
//  urlChars.replace("%F2", "Ã²");
//  urlChars.replace("%F3", "Ã³");
//  urlChars.replace("%F4", "Ã´");
//  urlChars.replace("%F5", "Ãµ");
//  urlChars.replace("%F6", "Ã¶");
//  urlChars.replace("%F7", "Ã·");
//  urlChars.replace("%F8", "Ã¸");
//  urlChars.replace("%F9", "Ã¹");
//  urlChars.replace("%FA", "Ãº");
//  urlChars.replace("%FB", "Ã»");
//  urlChars.replace("%FC", "Ã¼");
//  urlChars.replace("%FD", "Ã½");
//  urlChars.replace("%FE", "Ã¾");
//  urlChars.replace("%FF", "Ã¿");
//
//  return urlChars;
//}
