/******* STARTUP PANEL *******/

void startPanels(){
  panLogo(); // Display our logo  
  do_converts(); // load the unit conversion preferences
}

//------------------ Panel: Startup ArduCam OSD LOGO -------------------------------

void panLogo(){
    osd.setPanel(5, 5);
    osd.openPanel();
    osd.printf_P(PSTR("\xb0\xb1\xb2\xb3\xb4|\xb5\xb6\xb7\xb8\xb9|MinimOSD-Extra Copter|Pre-Release r605"));
    osd.closePanel();
}


/******* PANELS - POSITION *******/

void writePanels(){ 
//  if(millis() < (lastMAVBeat + 2200))
//    waitingMAVBeats = 1;
  //if(ISd(panel,Warn_BIT)) panWarn(panWarn_XY[0][panel], panWarn_XY[1][panel]); // this must be here so warnings are always checked

  //Only show flight summary 10 seconds after landing and if throttle < 15
  if ((landed_at_time != 4294967295) && ((((millis() - landed_at_time) / 10000) % 2) == 0)){ 
    if (osd_clear == 0){
       osd.clear();
       osd_clear = 1;
    }
    panFdata(); 
  }else{ 
    if(ISd(0,Warn_BIT)) panWarn(panWarn_XY[0][0], panWarn_XY[1][0]); // this must be here so warnings are always checked
    //Check for panel toggle
    if(ch_toggle > 3) panOff(); // This must be first so you can always toggle
    if (osd_clear == 1){
      osd.clear();
      osd_clear = 0;
    }
    if(panel != npanels){
      //Testing bits from 8 bit register A 
      //if(ISa(panel,Cen_BIT)) panCenter(panCenter_XY[0][panel], panCenter_XY[1][panel]);   //4x2
      if(ISa(panel,Pit_BIT)) panPitch(panPitch_XY[0][panel], panPitch_XY[1][panel]); //5x1
      if(ISa(panel,Rol_BIT)) panRoll(panRoll_XY[0][panel], panRoll_XY[1][panel]); //5x1
      if(ISa(panel,BatA_BIT)) panBatt_A(panBatt_A_XY[0][panel], panBatt_A_XY[1][panel]); //7x1
      //if(ISa(panel,BatB_BIT)) panBatt_B(panBatt_B_XY[0], panBatt_B_XY[1][panel]); //7x1
      if(ISa(panel,GPSats_BIT)) panGPSats(panGPSats_XY[0][panel], panGPSats_XY[1][panel]); //5x1
      //if(ISa(panel,GPL_BIT)) panGPL(panGPL_XY[0][panel], panGPL_XY[1][panel]); //2x1
      if(ISa(panel,GPS_BIT)) panGPS(panGPS_XY[0][panel], panGPS_XY[1][panel]); //12x3
      if(ISa(panel,Bp_BIT)) panBatteryPercent(panBatteryPercent_XY[0][panel], panBatteryPercent_XY[1][panel]); //
      if(ISa(panel,COG_BIT)) panCOG(panCOG_XY[0][panel], panCOG_XY[1][panel]); //

      //Testing bits from 8 bit register B
      if(ISb(panel,Rose_BIT)) panRose(panRose_XY[0][panel], panRose_XY[1][panel]);        //13x3
      if(ISb(panel,Head_BIT)) panHeading(panHeading_XY[0][panel], panHeading_XY[1][panel]); //13x3
      //if(ISb(panel,MavB_BIT)) panMavBeat(panMavBeat_XY[0][panel], panMavBeat_XY[1][panel]); //13x3
      if(osd_got_home == 1){
        if(ISb(panel,HDis_BIT)) panHomeDis(panHomeDis_XY[0][panel], panHomeDis_XY[1][panel]); //13x3
        if(ISb(panel,HDir_BIT)) panHomeDir(panHomeDir_XY[0][panel], panHomeDir_XY[1][panel]); //13x3
      }
      if(ISb(panel,Time_BIT)) panTime(panTime_XY[0][panel], panTime_XY[1][panel]);
      if(ISb(panel,WDis_BIT)) panWPDis(panWPDis_XY[0][panel], panWPDis_XY[1][panel]); //??x??

      //Testing bits from 8 bit register C 
      //if(osd_got_home == 1){
      if(ISc(panel,Alt_BIT)) panAlt(panAlt_XY[0][panel], panAlt_XY[1][panel]); //
      if(ISc(panel,Halt_BIT)) panHomeAlt(panHomeAlt_XY[0][panel], panHomeAlt_XY[1][panel]); //
      if(ISc(panel,Vel_BIT)) panVel(panVel_XY[0][panel], panVel_XY[1][panel]); //
      if(ISc(panel,As_BIT)) panAirSpeed(panAirSpeed_XY[0][panel], panAirSpeed_XY[1][panel]); //
      //}
      if(ISc(panel,Thr_BIT)) panThr(panThr_XY[0][panel], panThr_XY[1][panel]); //
      if(ISc(panel,FMod_BIT)) panFlightMode(panFMod_XY[0][panel], panFMod_XY[1][panel]);  //
      if(ISc(panel,Hor_BIT)) panHorizon(panHorizon_XY[0][panel], panHorizon_XY[1][panel]); //14x5
      if(ISc(panel,CurA_BIT)) panCur_A(panCur_A_XY[0][panel], panCur_A_XY[1][panel]);

      //Testing bits from 8 bit register D 
      //if(ISd(Off_BIT)) panOff(panOff_XY[0], panOff_XY[1]);
      //For now we don't have windspeed in copter
      //if(ISd(panel,WindS_BIT)) panWindSpeed(panWindSpeed_XY[0][panel], panWindSpeed_XY[1][panel]);
      if(ISd(panel,Climb_BIT)) panClimb(panClimb_XY[0][panel], panClimb_XY[1][panel]);
      //if(ISd(panel,Tune_BIT)) panTune(panTune_XY[0][panel], panTune_XY[1][panel]);
      if(ISd(panel,RSSI_BIT)) panRSSI(panRSSI_XY[0][panel], panRSSI_XY[1][panel]); //??x??
      if(ISd(panel,Eff_BIT)) panEff(panEff_XY[0][panel], panEff_XY[1][panel]);
      //if(ISd(panel,CALLSIGN_BIT)) panCALLSIGN(panCALLSIGN_XY[0][panel], panCALLSIGN_XY[1][panel]);
      if(ISe(panel,TEMP_BIT)) panTemp(panTemp_XY[0][panel], panTemp_XY[1][panel]);
      //if(ISe(panel,Ch_BIT)) panCh(panCh_XY[0][panel], panCh_XY[1][panel]);
      if(ISe(panel,DIST_BIT)) panDistance(panDistance_XY[0][panel], panDistance_XY[1][panel]);
    }
    //else { //panel == npanels
      //if(ISd(0,Warn_BIT)) panWarn(panWarn_XY[0][0], panWarn_XY[1][0]); // this must be here so warnings are always checked
      //if(ISd(0,CALLSIGN_BIT)) panCALLSIGN(panCALLSIGN_XY[0][panel], panCALLSIGN_XY[1][panel]); //call sign even in off panel
    //}
  }
/*  } else { // if no mavlink update for 2 secs
    
        // this could be replaced with a No Mavlink warning so the last seen values still show

        osd.clear();
        waitingMAVBeats = 1;
        // Display our logo and wait... 
    //    panWaitMAVBeats(5,10); //Waiting for MAVBeats...
    panLogo();
  }*/
  if(ISd(panel % npanels,CALLSIGN_BIT)) panCALLSIGN(panCALLSIGN_XY[0][panel], panCALLSIGN_XY[1][panel]); //call sign even in off panel
  
    // OSD debug for development (Shown on top-middle panels) 
#ifdef membug
    osd.setPanel(13,4);
    osd.openPanel();
    osd.printf("%i",freeMem()); 
    osd.closePanel();
#endif
}

/******* PANELS - DEFINITION *******/
/* **************************************************************** */

/* **************************************************************** */
// Panel  : COG Course Over Ground
// Needs  : X, Y locations
// Output : 
// Size   : 
// Staus  : done

void panCOG(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    
    off_course = (osd_cog / 100 - osd_heading) ; //[-360, 360]
    osd_COG_arrow_rotate_int = ((int)round((float)(off_course/360.0) * 16.0) + 16) % 16 + 1; //[1, 16]
    //if(osd_COG_arrow_rotate_int < 0 ) osd_COG_arrow_rotate_int += 16; //Normalize [0, 16]
    //osd_COG_arrow_rotate_int = osd_COG_arrow_rotate_int % 16 + 1; //[1, 16]
    if (off_course > 180){
       off_course += - 360;
    }else if (off_course < -180){
       off_course += + 360;
    }
    showArrow((uint8_t)osd_COG_arrow_rotate_int,2);
    osd.closePanel();
}

// Panel  : ODO
// Needs  : X, Y locations
// Output : 
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panDistance(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    //do_converts();
    if ((tdistance * converth) > 1000.0) {
    osd.printf("%c%5.2f%c", 0x8F, ((tdistance * converth) / distconv), distchar);
    }else{
    osd.printf("%c%5.0f%c", 0x8F, (tdistance * converth), high);
    }
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panFdata
// Needs  : X, Y locations
// Output : 
// Size   : 
// Staus  : done
void panFdata(){
     osd.setPanel(11, 4);
    osd.openPanel();                          
//    osd.printf("%c%3i%c%02i|%c%5.0f%c|%c%5.0f%c|%c%5.0f%c|%c%5.0f%c|%c%5.0f%c|%c%5.0f%c", 0x08,((int)start_Time/60)%60,0x3A,(int)start_Time%60, 0x0B, ((max_home_distance) * converth), high, 0x1B, ((tdistance) * converth), high, 0x13,(max_osd_airspeed * converts), spe,0x14,(max_osd_groundspeed * converts),spe,0x12, (max_osd_home_alt * converth), high,0x1D,(max_osd_windspeed * converts),spe);
//    osd.printf("%c%3i%c%02i|%c%5i%c|%c%5i%c|%c%5i%c|%c%5i%c|%c%5i%c|%c%5i%c|%c%10.6f|%c%10.6f", 0x08,((int)start_Time/60)%60,0x3A,(int)start_Time%60, 0x0B, (int)((max_home_distance) * converth), high, 0x8F, (int)((tdistance) * converth), high, 0x13,(int)(max_osd_airspeed * converts), spe,0x14,(int)(max_osd_groundspeed * converts),spe,0x12, (int)(max_osd_home_alt * converth), high,0x1D,(int)(max_osd_windspeed * converts),spe, 0x03, (double)osd_lat, 0x04, (double)osd_lon);
    osd.printf("%c%3i%c%02i|%c%5i%c|%c%5i%c|%c%5i%c|%c%5i%c|%c%10.6f|%c%10.6f", 0x08,((int)start_Time/60)%60,0x3A,(int)start_Time%60, 0x0B, (int)((max_home_distance) * converth), high, 0x8F, (int)((tdistance) * converth), high,0x14,(int)(max_osd_groundspeed * converts),spe,0x12, (int)(max_osd_home_alt * converth), high, 0x03, (double)osd_lat, 0x04, (double)osd_lon);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : pantemp
// Needs  : X, Y locations
// Output : 
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panTemp(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    //do_converts();
    osd.printf("%c%5.1f%c", 0x0a, (float(temperature / 10 * tempconv + tempconvAdd) / 100), temps);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : efficiency
// Needs  : X, Y locations
// Output : 
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panEff(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    //Check takeoff just to prevent inicial false readings
    if (takeofftime){
        ////If in loiter should estimated remaining flight time
        //if ((osd_climb > -0.05) && (osd_climb < 0.05) && (osd_groundspeed * converts < 2)){ 
          if(osd_battery_remaining_A != last_battery_reading){
            remaining_Time = osd_battery_remaining_A * ((millis()/1000) - FTime) / (start_battery_reading - osd_battery_remaining_A);
            last_battery_reading = osd_battery_remaining_A;
          }
          osd.printf("%c%2i%c%02i", 0x17,((int)remaining_Time/60)%60,0x3A,(int)remaining_Time%60);
        //}
        //If in movement show mAh needed to fly a Km or a mile (depending on selected unit
//        else{
//          eff = (float(osd_curr_A * 10) / (osd_groundspeed * converts))* 0.5 + eff * 0.5;
//        eff = eff * 0.2 + eff * 0.8;
//          if (eff > 0 && eff <= 9999) {
//            osd.printf("%c%4.0f%c", 0x17, (double)eff, 0x82);
//          }else{
//          osd.printf_P(PSTR("\x17\x20\x20\x20\x20\x20")); 
//          }
        //}
    }
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panCh
// Needs  : X, Y locations
// Output : Scaled channel values from MAVLink
// Size   
// Staus  : done

//void panCh(int first_col, int first_line){
//    osd.setPanel(first_col, first_line);
//    osd.openPanel();
    
//    osd.printf("%c%c%5i|%c%c%5i|%c%c%5i|%c%c%5i|%c%c%5i|%c%c%5i", 0x43, 0x31, chan1_raw, 0x43, 0x32, chan2_raw, 0x43, 0x33, chan3_raw, 0x43, 0x34, chan4_raw, 0x43, 0x35, chan5_raw, 0x43, 0x36, chan6_raw); 
//    osd.closePanel();
//}

/* **************************************************************** */
// Panel  : panRSSI
// Needs  : X, Y locations
// Output : Alt symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panRSSI(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    rssi = (int16_t)osd_rssi;
    //if (rssi > rssical) rssi = rssical;
    //else if (rssi < rssipersent) rssi = rssipersent;

    if(!rssiraw_on) rssi = (int16_t)((float)(rssi - rssipersent)/(float)(rssical-rssipersent)*100.0f);
//    if (rssi < -99) rssi = -99;
    osd.printf("%c%3i%c", 0x09, rssi, 0x25);
//    osd.printf("%c%3i%c", 0x09, osd_clear, 0x25); 
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panCALLSIGN
// Needs  : X, Y locations
// Output : Call sign identification
// Size   : 1 x 6Hea  (rows x chars)
// Staus  : done

void panCALLSIGN(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    //osd.printf("%c%c%c%c%c%c", char_call[0], char_call[1], char_call[2], char_call[3], char_call[4], char_call[5]); 
    //During the first 1000 miliseconds of each minute show callsign
    if(((millis() / 1000) % 60) < 2)
      osd.printf("%s", char_call);
    else
//    osd.printf_P(PSTR("\x20\x20\x20\x20\x20\x20\x20\x20"));
      osd.printf("%s",strclear);
    
/*    if ((millis() - 60000) > CallSignBlink){
      if (millis() - 61000 > CallSignBlink){
        CallSignBlink = (millis() - 1000);
          }
    osd.printf("%s", char_call); 
    }else{
//    osd.printf_P(PSTR("\x20\x20\x20\x20\x20\x20\x20\x20"));
    osd.printf("%s",strclear);
    }*/
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panSetup
// Needs  : Nothing, uses whole screen
// Output : The settings menu
// Size   : 3 x ?? (rows x chars)
// Staus  : done

//void panSetup(){

//    if (millis() > text_timer){
//        text_timer = millis() + 500;

//        osd.clear();
//        osd.setPanel(5, 7);
//        osd.openPanel();

//        if (chan1_raw_middle == 0 && chan2_raw_middle == 0){
//            chan1_raw_middle = chan1_raw;
//            chan2_raw_middle = chan2_raw;
//        }

//        if ((chan2_raw - 100) > chan2_raw_middle ) setup_menu++;  //= setup_menu + 1;
//        else if ((chan2_raw + 100) < chan2_raw_middle ) setup_menu--;  //= setup_menu - 1;
//        if (setup_menu < 0) setup_menu = 0;
//        else if (setup_menu > 2) setup_menu = 2;


//        switch (setup_menu){
//        case 0:
//            {
//                osd.printf_P(PSTR("    Overspeed    "));
//                osd.printf("%3.0i%c", overspeed, spe);
//                overspeed = change_val(overspeed, overspeed_ADDR);
//                break;
//            }
//        case 1:
//            {
//                osd.printf_P(PSTR("   Stall Speed   "));
//                osd.printf("%3.0i%c", stall , spe);
//                //overwritedisplay();
//                stall = change_val(stall, stall_ADDR);
//                break;
//            }
//        case 2:
//            {
//                osd.printf_P(PSTR("Battery warning "));
//                osd.printf("%3.1f%c", float(battv)/10.0 , 0x76, 0x20);
//                battv = change_val(battv, battv_ADDR);
//                break;
//            }
            //      case 4:
            //        osd.printf_P(PSTR("Battery warning "));
            //        osd.printf("%3.0i%c", battp , 0x25);
            //        if ((chan1_raw - 100) > chan1_raw_middle ){
            //        battp = battp - 1;}
            //        if ((chan1_raw + 100) < chan1_raw_middle ){
            //        battp = battp + 1;} 
            //        EEPROM.write(208, battp);
            //        break;
//        }
//}
//    osd.closePanel();
//}

//int change_val(int value, int address)
//{
//    uint8_t value_old = value;
//    if (chan1_raw > chan1_raw_middle + 100) value--;
//    if (chan1_raw  < chan1_raw_middle - 100) value++;

//    if(value != value_old && setup_menu ) EEPROM.write(address, value);
//    return value;
//}

/* **************************************************************** */
// Panel  : pan wind speed
// Needs  : X, Y locations
// Output : Wind direction symbol (arrow) and velocity
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panWindSpeed(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();

    //osd_wind_arrow_rotate_int = round((osd_winddirection - osd_heading)/360.0 * 16.0) + 1; //Convert to int 1-16
    //if(osd_wind_arrow_rotate_int < 0 ) osd_wind_arrow_rotate_int += 16; //normalize
    //else if(osd_wind_arrow_rotate_int == 0 ) osd_wind_arrow_rotate_int = 1; //normalize
    //else if(osd_wind_arrow_rotate_int == 17 ) osd_wind_arrow_rotate_int = 1; //normalize
    
    osd_wind_arrow_rotate_int = ((int)round((osd_winddirection - osd_heading)/360.0 * 16.0) + 16) % 16 + 1; //[1, 16]
    nor_osd_windspeed = osd_windspeed * 0.010 + nor_osd_windspeed * 0.990;     
    showArrow((uint8_t)osd_wind_arrow_rotate_int,1); //print data to OSD
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panOff
// Needs  : X, Y locations
// Output : OSD off
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panOff(){
  bool rotatePanel = 0;

  //If there is a warning force switch to panel 0
  if(foundWarning == 1){
    if(panel != 0){
      //osd.clear();
      osd_clear = 1;
    }
    panel = 0;
  }
  else{
    //Flight mode switching
    if (ch_toggle == 4){
      if ((osd_mode != 6) && (osd_mode != 7)){
        if (osd_off_switch != osd_mode){ 
          osd_off_switch = osd_mode;
            osd_switch_time = millis();
            if (osd_off_switch == osd_switch_last){
              rotatePanel = 1;
            }
        }
        if ((millis() - osd_switch_time) > 2000){
          osd_switch_last = osd_mode;
        }
      }
    }
    else {
      if(ch_toggle == 5) ch_raw = chan5_raw;
      else if(ch_toggle == 6) ch_raw = chan6_raw;
      else if(ch_toggle == 7) ch_raw = chan7_raw;
      else if(ch_toggle == 8) ch_raw = chan8_raw;

      //Switch mode by value
      if (switch_mode == 0){
        //First panel
        if (ch_raw < 1200 && panel != 0) {
          osd_clear = 1;
          //osd.clear();
          panel = 0;
        }
        //Second panel
        else if (ch_raw >= 1200 && ch_raw <= 1800 && panel != 1) { //second panel
          osd_clear = 1;
          //osd.clear();
          panel = 1;
        }
        //Panel off
        else if (ch_raw > 1800 && panel != npanels) {
          osd_clear = 1;
          //osd.clear();
          panel = npanels; //off panel
        }
      }
      //Rotation switch
      else{
        if (ch_raw > 1200)
          if (osd_switch_time + 1000 < millis()){
            rotatePanel = 1;
            osd_switch_time = millis();
        }
      }    
    }
    if(rotatePanel == 1){
      osd_clear = 1;
      //osd.clear();
      panel++;
      if (panel > npanels)
        panel = 0;
    }
  }
}
//* **************************************************************** */
// Panel  : panTune
// Needs  : X, Y locations
// Output : Current symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done
    
//  void panTune(int first_col, int first_line){
//  osd.setPanel(first_col, first_line);
//  osd.openPanel();

//  osd.printf("%c%c%2.0f%c|%c%c%2.0f%c|%c%c%4.0i%c|%c%c%4.0i%c|%c%c%3.0f%c|%c%c%3.0f%c|%c%c%3.0f%c", 0x4E, 0x52, (nav_roll), 0x05, 0x4E, 0x50, (nav_pitch), 0x05, 0x4E, 0x48, (nav_bearing), 0x05, 0x54, 0x42, (wp_target_bearing), 0x05, 0x41, 0x45, (alt_error * converth), high, 0x58, 0x45, (xtrack_error), 0x6D, 0x41, 0x45, ((aspd_error / 100.0) * converts), spe);

//  osd.closePanel();
//}

/* **************************************************************** */
// Panel  : panCur_A
// Needs  : X, Y locations
// Output : Current symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panCur_A(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    osd.printf("%c%5.2f%c", 0xBD, (float(osd_curr_A) * .01), 0x0E);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panAlt
// Needs  : X, Y locations
// Output : Alt symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panAlt(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    //osd.printf("%c%5.0f%c",0x11, (double)(osd_alt - osd_home_alt), 0x0C);
    osd.printf("%c%5.0f%c",0x11, (double)(osd_gps_alt * converth), high);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panClimb
// Needs  : X, Y locations
// Output : Alt symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panClimb(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    vs = (osd_climb * converth * 60) * 0.1 + vs * 0.9;
    osd.printf("%c%4.0f%c",0x15, vs, climbchar);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panHomeAlt
// Needs  : X, Y locations
// Output : Alt symbol and home altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panHomeAlt(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    osd.printf("%c%5.0f%c",0x12, (double)(osd_alt_to_home * converth), high);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panVel
// Needs  : X, Y locations
// Output : Velocity value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panVel(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    
    osd.printf("%c%3.0f%c",0x14,(double)(osd_groundspeed * converts),spe);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panAirSpeed
// Needs  : X, Y locations
// Output : Airspeed value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panAirSpeed(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    osd.printf("%c%3.0f%c", 0x13, (double)(osd_airspeed * converts), spe);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panWarn
// Needs  : X, Y locations
// Output : Airspeed value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panWarn(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();

    //If disarmed force showing disarmed message
    if (motor_armed == 0){
      warning_string = "\x20\x20\x44\x49\x53\x41\x52\x4d\x45\x44\x20\x20";
      warning_type = 10;
      text_timer = millis();
      foundWarning = 0;
    }

    //If there is no warning beeing shown, check for next one
    if(warning_type == 0){
      //byte check_warning = last_warning ++; // start the warning checks where we left it last time
      last_warning ++; // start the warning checks where we left it last time
      //while (check_warning != last_warning){
        //if (check_warning > 5) check_warning = 1; // change the 5 if you add more warning types
        if (last_warning > 5) last_warning = 1; // change the 5 if you add more warning types
        //Check for no GPS fix
        if(last_warning == 1){
          if ((osd_fix_type) < 2){
            warning_type = 1; // No GPS Fix
            warning_string = "\x20\x4E\x6F\x20\x47\x50\x53\x20\x66\x69\x78\x21";
          }
        }
        //Check for low airspeed
        else if(last_warning == 2){
          if (osd_airspeed * converts < stall && osd_airspeed > 1.12){
            warning_type = 2;
            warning_string = "\x20\x20\x20\x53\x74\x61\x6c\x6c\x21\x20\x20\x20";
          }
        }
        //Check for over speed
        else if(last_warning == 3){
          if ((osd_airspeed * converts) > (float)overspeed){
            warning_type = 3;
            warning_string = "\x20\x4f\x76\x65\x72\x53\x70\x65\x65\x64\x21\x20";
          }
        }
        //Check for low battery
        else if(last_warning == 4){
          if (osd_vbat_A < float(battv)/10.0 || (osd_battery_remaining_A < batt_warn_level && batt_warn_level != 0)){
            warning_type = 4;
            warning_string = "\x42\x61\x74\x74\x65\x72\x79\x20\x4c\x6f\x77\x21";
          }
        }
        //Check for low RSSI
        else if(last_warning == 5){
          if (rssi < rssi_warn_level && rssi != -99 && !rssiraw_on){
            warning_type = 5;
            warning_string = "\x20\x20\x4c\x6f\x77\x20\x52\x73\x73\x69\x20\x20";
          }
        }
        //Check next warning
        //check_warning ++;
        foundWarning = (warning_type > 0);
        if(warning_type != 0){
          text_timer = millis();
        }
      //}
    }
    else{
      if (millis() - text_timer > 2000){
        warning_type = 0;
      }
      else if (millis() - text_timer > 1000){
        warning_string = "\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20";
      }
      osd.printf("%s",warning_string);
    }
    osd.closePanel();
}

  
/* **************************************************************** */
// Panel  : panThr
// Needs  : X, Y locations
// Output : Throttle value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panThr(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    osd.printf("%c%3.0i%c",0x02,osd_throttle,0x25);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panBatteryPercent
// Needs  : X, Y locations
// Output : Battery state from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panBatteryPercent(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    if (EEPROM.read(OSD_BATT_SHOW_PERCENT_ADDR ) == 0){ 
      osd.printf("%c%4.0f%c",0x17, mah_used, 0x01); 
    }else{ 
      osd.printf("%c%3.0i%c", 0x17, osd_battery_remaining_A, 0x25); 
    } 
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panTime
// Needs  : X, Y locations
// Output : Time from start with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panTime(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    
    //start_Time = (millis()/1000) - FTime;
    osd.printf("%c%2i%c%02i", 0x08,((int)start_Time/60)%60,0x3A,(int)start_Time%60);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panHomeDis
// Needs  : X, Y locations
// Output : Home Symbol with distance to home in meters
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panHomeDis(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    osd.printf("%c%5.0f%c", 0x0B, (double)((osd_home_distance) * converth), high);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panCenter
// Needs  : X, Y locations
// Output : 2 row croshair symbol created by 2 x 4 chars
// Size   : 2 x 4  (rows x chars)
// Staus  : done

//void panCenter(int first_col, int first_line){
//    osd.setPanel(first_col, first_line);
//    osd.openPanel();
//    osd.printf_P(PSTR("\x05\x03\x04\x05|\x15\x13\x14\x15"));
//    osd.closePanel();
//}

/* **************************************************************** */
// Panel  : panHorizon
// Needs  : X, Y locations
// Output : 12 x 4 Horizon line surrounded by 2 cols (left/right rules)
// Size   : 14 x 4  (rows x chars)
// Staus  : done

void panHorizon(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
  
    osd.printf_P(PSTR("\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20|\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20|\xC6\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xC5\x20|\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20|\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"));

    osd.closePanel();
    showHorizon((first_col + 1), first_line);
    //Show ground level on  HUD
    showILS(first_col, first_line);
}

/* **************************************************************** */
// Panel  : panPitch
// Needs  : X, Y locations
// Output : -+ value of current Pitch from vehicle with degree symbols and pitch symbol
// Size   : 1 x 6  (rows x chars)
// Staus  : done

void panPitch(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    osd.printf("%4i%c%c",osd_pitch,0x05,0x07);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panRoll
// Needs  : X, Y locations
// Output : -+ value of current Roll from vehicle with degree symbols and roll symbol
// Size   : 1 x 6  (rows x chars)
// Staus  : done

void panRoll(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    osd.printf("%4i%c%c",osd_roll,0x05,0x06);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panBattery A (Voltage 1)
// Needs  : X, Y locations
// Output : Voltage value as in XX.X and symbol of over all battery status
// Size   : 1 x 8  (rows x chars)
// Staus  : done

void panBatt_A(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    /*************** This commented code is for the next ArduPlane Version
    if(osd_battery_remaining_A > 100){
        osd.printf(" %c%5.2f%c", 0xBD, (double)osd_vbat_A, 0xC9);
    else osd.printf("%c%5.2f%c%c", 0xBD, (double)osd_vbat_A, 0xC9, osd_battery_pic_A);
    */
    osd.printf("%c%5.2f%c", 0xBC, (double)osd_vbat_A, 0x0D);
    osd.closePanel();
}

//------------------ Panel: Waiting for MAVLink HeartBeats -------------------------------

//void panWaitMAVBeats(int first_col, int first_line){
//    panLogo();
//    osd.setPanel(first_col, first_line);
//    osd.openPanel();
//    osd.printf_P(PSTR("Waiting for|MAVLink heartbeats..."));
//    osd.closePanel();
//}

/* **************************************************************** */
// Panel  : panGPL
// Needs  : X, Y locations
// Output : 1 static symbol with changing FIX symbol
// Size   : 1 x 2  (rows x chars)
// Staus  : done

void panGPL(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    char* gps_str;
    if(osd_fix_type == 0 || osd_fix_type == 1) gps_str = "\x1F\x20"; 
        //osd.printf_P(PSTR("\x1F\x20"));
    else if(osd_fix_type == 2 || osd_fix_type == 3) gps_str = "\x0F\x20";
        //osd.printf_P(PSTR("\x0F\x20"));
    osd.printf("%s",gps_str);

    /*  if(osd_fix_type <= 1) {
    osd.printf_P(PSTR("\x1F"));
    } else {
    osd.printf_P(PSTR("\x0F"));
    }  */
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panGPSats
// Needs  : X, Y locations
// Output : 1 symbol and number of locked satellites
// Size   : 1 x 5  (rows x chars)
// Staus  : done

void panGPSats(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    
    char* gps_str;
    if(osd_fix_type == 0 || osd_fix_type == 1) gps_str = "\x1F";       
    else if(osd_fix_type == 2 || osd_fix_type == 3) gps_str = "\x0F";
    
    osd.printf("%s%2i", gps_str, osd_satellites_visible);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panGPS
// Needs  : X, Y locations
// Output : two row numeric value of current GPS location with LAT/LON symbols as on first char
// Size   : 2 x 12  (rows x chars)
// Staus  : done

void panGPS(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    osd.printf("%c%10.6f|%c%10.6f", 0x03, (double)osd_lat, 0x04, (double)osd_lon);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panHeading
// Needs  : X, Y locations
// Output : Symbols with numeric compass heading value
// Size   : 1 x 5  (rows x chars)
// Staus  : not ready

void panHeading(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    osd.printf("%4.0f%c", (double)osd_heading, 0x05);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panRose
// Needs  : X, Y locations
// Output : a dynamic compass rose that changes along the heading information
// Size   : 2 x 13  (rows x chars)
// Staus  : done

void panRose(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    //osd_heading  = osd_yaw;
    //if(osd_yaw < 0) osd_heading = 360 + osd_yaw;
    //osd.printf("%s|%c%s%c", "\x20\x80\x80\x80\x80\x80\x81\x80\x80\x80\x80\x80\x20", 0xc3, buf_show, 0x87);
    osd.printf("%c%s%c", 0xc3, buf_show, 0x87);
    osd.closePanel();
}


/* **************************************************************** */
// Panel  : panBoot
// Needs  : X, Y locations
// Output : Booting up text and empty bar after that
// Size   : 1 x 21  (rows x chars)
// Staus  : done

/*void panBoot(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    osd.printf_P(PSTR("Booting up:\x88\x8D\x8D\x8D\x8D\x8D\x8D\x8D\x8E")); 
    osd.closePanel();
}*/

/* **************************************************************** */
// Panel  : panMavBeat
// Needs  : X, Y locations
// Output : 2 symbols, one static and one that blinks on every 50th received 
//          mavlink packet.
// Size   : 1 x 2  (rows x chars)
// Staus  : done

//void panMavBeat(int first_col, int first_line){
//    osd.setPanel(first_col, first_line);
//    osd.openPanel();
//    if(mavbeat == 1){
//        osd.printf_P(PSTR("\xEA\xEC"));
//        mavbeat = 0;
//    }
//    else{
//        osd.printf_P(PSTR("\xEA\xEB"));
//    }
//    osd.closePanel();
//}


/* **************************************************************** */
// Panel  : panWPDir
// Needs  : X, Y locations
// Output : 2 symbols that are combined as one arrow, shows direction to next waypoint
// Size   : 1 x 2  (rows x chars)
// Staus  : not ready

//void panWPDir(int first_col, int first_line){
//    osd.setPanel(first_col, first_line);
//    osd.openPanel();
   
//    wp_target_bearing_rotate_int = round(((float)wp_target_bearing - osd_heading)/360.0 * 16.0) + 1; //Convert to int 0-16 
//    if(wp_target_bearing_rotate_int < 0 ) wp_target_bearing_rotate_int += 16; //normalize  

//    showArrow((uint8_t)wp_target_bearing_rotate_int,0);
//    osd.closePanel();
//}

/* **************************************************************** */
// Panel  : panWPDis
// Needs  : X, Y locations
// Output : W then distance in Km - Distance to next waypoint
// Size   : 1 x 2  (rows x chars)
// Staus  : not ready TODO - CHANGE the Waypoint symbol - Now only a W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void panWPDis(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    
    //wp_target_bearing_rotate_int = (int)round(((float)wp_target_bearing - osd_heading)/360.0 * 16.0); //[-16, 16]
    //if(wp_target_bearing_rotate_int < 0 ) wp_target_bearing_rotate_int += 16; //normalize [0, 16]
    //wp_target_bearing_rotate_int = wp_target_bearing_rotate_int % 16 + 1; //Convert to [1, 16] 
    wp_target_bearing_rotate_int = ((int)round(((float)wp_target_bearing - osd_heading)/360.0 * 16.0) + 16) % 16 + 1; //[1, 16]
    
    if (xtrack_error > 999) xtrack_error = 999;
    else if (xtrack_error < -999) xtrack_error = -999;

    osd.printf("%c%c%2i%c%4.0f%c|",0x57, 0x70, wp_number,0x0,(double)((float)(wp_dist) * converth),high);
    showArrow((uint8_t)wp_target_bearing_rotate_int,0);
    if (osd_mode == 10){
        osd.printf("%c%c%c%4.0f%c", 0x20, 0x58, 0x65, (xtrack_error* converth), high);
    }else{
        osd.printf_P(PSTR("\x20\x20\x20\x20\x20\x20\x20\x20"));
    }
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panHomeDir
// Needs  : X, Y locations
// Output : 2 symbols that are combined as one arrow, shows direction to home
// Size   : 1 x 2  (rows x chars)
// Status : not tested

void panHomeDir(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    showArrow((uint8_t)osd_home_direction,0);
    osd.closePanel();
}

/* **************************************************************** */
// Panel  : panFlightMode 
// Needs  : X, Y locations
// Output : 2 symbols, one static name symbol and another that changes by flight modes
// Size   : 1 x 2  (rows x chars)
// Status : done

void panFlightMode(int first_col, int first_line){
    osd.setPanel(first_col, first_line);
    osd.openPanel();
    //char c1 = 0xE0 ;//"; char c2; char c3; char c4; char c5; 
    char* mode_str="";
    if (osd_mode == 0) mode_str = "stab"; //Stabilize
    else if (osd_mode == 1) mode_str = "acro"; //Acrobatic
    else if (osd_mode == 2) mode_str = "alth"; //Alt Hold
    else if (osd_mode == 3) mode_str = "auto"; //Auto
    else if (osd_mode == 4) mode_str = "guid"; //Guided
    else if (osd_mode == 5) mode_str = "loit"; //Loiter
    else if (osd_mode == 6) mode_str = "retl"; //Return to Launch
    else if (osd_mode == 7) mode_str = "circ"; //Circle
    else if (osd_mode == 8) mode_str = "posi"; //Position
    else if (osd_mode == 9) mode_str = "land"; //Land
    else if (osd_mode == 10) mode_str = "oflo"; //OF_Loiter
    osd.printf("%c%s%c", 0x7F, mode_str, motor_armed * 0x86);
    osd.closePanel();
}


// ---------------- EXTRA FUNCTIONS ----------------------
// Show those fancy 2 char arrows
void showArrow(uint8_t rotate_arrow,uint8_t method) {  
    int arrow_set1 = 0x90;
    //We trust that we receive rotate_arrow [1, 16] so 
    //it's no needed (rotate_arrow <= 16) in the if clause
    arrow_set1 += rotate_arrow * 2 - 2;
    //arrow_set2 = arrow_set1 + 1;
//    if(method == 1) osd.printf("%c%3.0f%c|%c%c%2.0f%c",0x1D,(double)(osd_windspeed * converts),spe, (byte)arrow_set1, (byte)(arrow_set1 + 1),(double)(osd_windspeedz * converts),spe);
    if(method == 1) osd.printf("%c%3.0f%c|%c%c%2.0f%c",0x1d,(double)(osd_windspeed * converts),spe, arrow_set1, arrow_set1 + 1,(double)(nor_osd_windspeed * converts),spe);
    else if(method == 2) osd.printf("%c%c%4i%c", arrow_set1, arrow_set1 + 1, off_course, 0x05);   
    else osd.printf("%c%c", arrow_set1, arrow_set1 + 1);
}

// Calculate and shows Artificial Horizon
// For using this, you must load a special mcm file with the new staggered artificial horizon chars!
// e.g. AH_BetterResolutionCharset002.mcm
							// with different factors we can adapt do different cam optics
#define AH_PITCH_FACTOR		0.010471976		// conversion factor for pitch
#define AH_ROLL_FACTOR		0.017453293		// conversion factor for roll
#define AH_COLS			12			// number of artificial horizon columns
#define AH_ROWS			5			// number of artificial horizon rows
#define CHAR_COLS		12			// number of MAX7456 char columns
#define CHAR_ROWS		18			// number of MAX7456 char rows
#define CHAR_SPECIAL		9			// number of MAX7456 special chars for the artificial horizon
#define AH_TOTAL_LINES		AH_ROWS * CHAR_ROWS	// helper define


#define LINE_SET_STRAIGHT__	(0xC7 - 1)		// code of the first MAX7456 straight char -1
#define LINE_SET_STRAIGHT_O	(0xD0 - 3)		// code of the first MAX7456 straight overflow char -3
#define LINE_SET_P___STAG_1	(0xD1 - 1)		// code of the first MAX7456 positive staggered set 1 char -1
#define LINE_SET_P___STAG_2	(0xDA - 1)		// code of the first MAX7456 positive staggered set 2 char -1
#define LINE_SET_N___STAG_1	(0xE3 - 1)		// code of the first MAX7456 negative staggered set 1 char -1
#define LINE_SET_N___STAG_2	(0xEC - 1)		// code of the first MAX7456 negative staggered set 2 char -1
#define LINE_SET_P_O_STAG_1	(0xF5 - 2)		// code of the first MAX7456 positive overflow staggered set 1 char -2
#define LINE_SET_P_O_STAG_2	(0xF9 - 1)		// code of the first MAX7456 positive overflow staggered set 2 char -1
#define LINE_SET_N_O_STAG_1	(0xF7 - 2)		// code of the first MAX7456 negative overflow staggered set 1 char -2
#define LINE_SET_N_O_STAG_2	(0xFC - 1)		// code of the first MAX7456 negative overflow staggered set 2 char -1


#define OVERFLOW_CHAR_OFFSET	6			// offset for the overflow subvals


#define ANGLE_1			9			// angle above we switch to line set 1
#define ANGLE_2			25			// angle above we switch to line set 2


// Calculate and show artificial horizon
// used formula: y = m * x + n <=> y = tan(a) * x + n
void showHorizon(int start_col, int start_row) {
    int col, row, pitch_line, middle, hit, subval;
    int roll;
    int line_set = LINE_SET_STRAIGHT__;
    int line_set_overflow = LINE_SET_STRAIGHT_O;
    int subval_overflow = 9;
    
    // preset the line char attributes
    roll = osd_roll;
    if ((roll >= 0 && roll < 90) || (roll >= -179 && roll < -90)) {	// positive angle line chars
	roll = roll < 0 ? roll + 179 : roll;
        if (abs(roll) > ANGLE_2) {
	    line_set = LINE_SET_P___STAG_2;
	    line_set_overflow = LINE_SET_P_O_STAG_2;
            subval_overflow = 7;
	} else if (abs(roll) > ANGLE_1) {
	    line_set = LINE_SET_P___STAG_1;
	    line_set_overflow = LINE_SET_P_O_STAG_1;
            subval_overflow = 8;
	}
    } else {								// negative angle line chars
	roll = roll > 90 ? roll - 179 : roll;
        if (abs(roll) > ANGLE_2) {
	    line_set = LINE_SET_N___STAG_2;
	    line_set_overflow = LINE_SET_N_O_STAG_2;
            subval_overflow = 7;
	} else if (abs(roll) > ANGLE_1) {
	    line_set = LINE_SET_N___STAG_1;
	    line_set_overflow = LINE_SET_N_O_STAG_1;
            subval_overflow = 8;
	}
    }
    
    pitch_line = round(tan(-AH_PITCH_FACTOR * osd_pitch) * AH_TOTAL_LINES) + AH_TOTAL_LINES/2;	// 90 total lines
    for (col=1; col<=AH_COLS; col++) {
        middle = col * CHAR_COLS - (AH_COLS/2 * CHAR_COLS) - CHAR_COLS/2;	  // -66 to +66	center X point at middle of each column
        hit = tan(AH_ROLL_FACTOR * osd_roll) * middle + pitch_line;	          // 1 to 90	calculating hit point on Y plus offset
        if (hit >= 1 && hit <= AH_TOTAL_LINES) {
	    row = (hit-1) / CHAR_ROWS;						  // 0 to 4 bottom-up
	    subval = (hit - (row * CHAR_ROWS) + 1) / (CHAR_ROWS / CHAR_SPECIAL);  // 1 to 9
	    
	    // print the line char
            osd.openSingle(start_col + col - 1, start_row + AH_ROWS - row - 1);
            osd.printf("%c", line_set + subval);
	    
	    // check if we have to print an overflow line char
	    if (subval >= subval_overflow && row < 4) {	// only if it is a char which needs overflow and if it is not the upper most row
                osd.openSingle(start_col + col - 1, start_row + AH_ROWS - row - 2);
                osd.printf("%c", line_set_overflow + subval - OVERFLOW_CHAR_OFFSET);
	    }
        }
    }
}

// Calculate and shows verical speed aid
void showILS(int start_col, int start_row) { 
    //Show line on panel center because horizon line can be
    //high or low depending on pitch attitude
    int subval_char = 0xCF;

    //shift alt interval from [-5, 5] to [0, 10] interval, so we
    //can work with remainders.
    //We are using a 0.2 altitude units as resolution (1 decimal place)
    //so convert we convert it to times 10 to work 
    //only with integers and save some bytes
    //int alt = (osd_alt_to_home * converth + 5) * 10;
    int alt = (osd_alt_to_home * converth + 5) * 4.4; //44 possible position 5 rows times 9 chars
    
    if((alt < 44) && (alt > 0)){
        //We have 9 possible chars
        //(alt * 5) -> 5 represents 1/5 which is our resolution. Every single
        //line (char) change represents 0,2 altitude units
        //% 10 -> Represents our 10 possible characters
        //9 - -> Inverts our selected char because when we gain altitude
        //the selected char has a lower position in memory
        //+ 5 -> Is the memory displacement od the first altitude charecter 
        //in memory (it starts at 0x05
        //subval_char = (99 - ((alt * 5) % 100)) / 9 + 0xC7;
        subval_char = (8 - (alt  % 9)) + 0xC7;
        //Each row represents 2 altitude units
        start_row += (alt / 9);
    }
    else if(alt >= 44){
        //Copter is too high. Ground is way too low to show on panel, 
        //so show down arrow at the bottom
        subval_char = 0xC8; 
        start_row += 4;
    }

    //Enough calculations. Let's show the result
    osd.openSingle(start_col + AH_COLS + 2, start_row);
    osd.printf("%c", subval_char);
}

void do_converts()
{
    if (EEPROM.read(measure_ADDR) == 0) {
        converts = 3.6;
        converth = 1.0;
        spe = 0x10;
        high = 0x0C;
        temps = 0xBA;
        tempconv = 10;
        tempconvAdd = 0;
        distchar = 0x1B;
        distconv = 1000;
        climbchar = 0x1A;
    } else {
        converts = 2.23;
        converth = 3.28;
        spe = 0x19;
        high = 0x66;
        temps = 0xBB;
        tempconv = 18;
        tempconvAdd = 3200;
        distchar = 0x1C;
        distconv = 5280;
        climbchar = 0x1E;
    }
}
