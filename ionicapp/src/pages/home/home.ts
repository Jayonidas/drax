import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {

  constructor(public navCtrl: NavController) {

  }

  openCloseBlastGate(gateID, open){

    var ip = "192.168.1.23";

    var url = "http://"+ip+"/openBlastGate?gate="+gateID+"&open="+open;
    fetch(url);

  }

  toggleRelay(relayID){

    var ip = "192.168.0.6";

    // Get Current Relay State and then Toggle Relay
    var queryUrl = "http://"+ip+"/queryRelay?relay="+relayID;
    fetch(queryUrl).then(function(response) {
      response.json().then(function(data) {
        
        // Toggle Relay
        var toggleUrl = "";

        console.log("State: "+data);

        if(data == 0){
          toggleUrl = "http://"+ip+"/toggleRelay?"+relayID+"=1";
        }
        if(data == 1){
          toggleUrl = "http://"+ip+"/toggleRelay?"+relayID+"=0";
        }

        fetch(toggleUrl);

      });
    });

  }

}
