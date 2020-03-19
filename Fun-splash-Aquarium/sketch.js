//3D Aquarium Game: "Fun Splash"
//fish model taken from: https://www.turbosquid.com/3d-models/free-tropical-fish-pack-3d-model/652729
//Help in loading 3D model: https://www.youtube.com/watch?v=FUI7HEEz9B0

var fish= [];  //to hold all fish within the aquarium
var fishCount; //in localstorage and in file
var fishStartTimes= []; //in localstorage and in file 
var scene; //determines which screens to display for the game
var coins; //number of coins the user has 
var fishTypes = [1,2]; //to hold different type of fish in the aquarium
var fishNames=[]; //to hold names of fish
var fishPics=[]; //to hold name of fish icon pictures of various fish types
var fishPrices=[]; //to hold price of different fish types
var cleanliness; //variable to determine the cleanliness of the tank 
var happiness; //variable to determine the happiness of the fish (equivalent to their food intake)
var fish1;  //to hold fish Type 1 model
var fish2;  //to hold fish Type 2 model
var fishMat1; //fish type 1 material  
var fishMat2; //fish type 2 material 
var fishMatSad1; //fish type 1 sad material  
var fishMatSad2; //fish type 2 sad material 
var fishbtn01; //variables to hold fish icon images
var fishbtn02;

var testFish; //to hold a test fish
var testFish2; //to hold another test fish
var fishStartSpeedsX= [1,2,3];
var fishStartSpeedsY= [-1,1];
var timeSinceStart;  //unix time stamp since the user started the game
var cleanResetTime;  //unix time stamp since the user last cleaned the tank
var foodResetTime; //unix time stamp since the user last fed fish
var coinResetTime; //unix time stamp to hold the coin time elapsed

var coinTimeLimit = 180; //time set in seconds for the coin limit 
var cleanlinessTimeLimit = 5;  //time set in seconds for the frequency with which water gets dirty
var foodTimeLimit= 10; //time set in seconds for the freqeucny with which fish get hungry
var myFont;
var totalBuyButtonCount; //flag to check/limit the number of buy buttons created

//UI variables
var environment; 
var statusBar;
var shopScreen;
var messageScreen;
var confirmScreen;
var shouldDisplayMsg;
var shouldDisplayConfirm;
var statusBarHeight =100;
var okButton;
var yesBtn;
var noBtn;

//shop variables
var shopClosebtn;
var buyBtns = [];
var buyBtn1;
var buyBtn2;

//////////////////////Fish Class///////////////////////
//functions and properties related to the fish class
//////////////////////Fish Class//////////////////////
function Fish(fishType,foodState,fishPrice){
    this.x= 0;
    this.y= 0;
    this.z=-30; //I want the fish to always stay behind all UI screens so they are initialized at this value
    this.rotateX=180;
    this.rotateY=90;
    this.rotateZ=0;
    this.speedX= fishStartSpeedsX[floor(random(0,2.9))];
    this.speedY=fishStartSpeedsY[floor(random(0,1.9))];
    this.speedZ= random(0.5,1.9);
    this.fishType = fishType;
    this.fishPrice= fishPrice;
    this.foodState= foodState;
    this.isAlive= true;
    this.fStartTime= Math.floor(Date.now()/1000); //UTC time for when fish was created
    this.foodTime= Math.floor(Date.now()/1000) - this.fStartTime; //time passed since last food was eaten
    
    //function to set the display of fish
    this.display= function(foodState){
        //food state 1 is to draw a happy fish
        if(foodState== 1)
            {
                //draw happy fish
                model(fish1);
                
            }
        else if(foodState==2)  //food state 2 is to draw unhappy fish
            {
                
            }
        else if(foodState==3)
            { //food state 3 is to draw dead fish

            }
    }
    this.updateFish= function()
    {   
        //keep updating time of fish since it was last fed
        //Moeezo Come back to this and fix time!
        this.foodTime= Math.floor(Date.now()/1000) - this.fStartTime;
        //console.log('time passed'+ this.foodTime);
        
        //updates the model for the fish  
         //food state 1 is to draw a happy fish
        if(foodState== 1)
            {
                //draw happy fish
                push();
                fill(255,0,0);
                translate(this.x,this.y,this.z);
                rotateX(this.rotateX);
                rotateY(this.rotateY);
                rotateZ(this.rotateZ);
                //rotate(this.rotateX,this.rotateY,this.rotateZ);
                normalMaterial(); //colorful rainbow
                if(fishType==1)
                    {
                    texture(fishMat1);    
                    model(fish1);
                    }
                else{
                   texture(fishMat2); 
                   model(fish2); 
                }
                pop();
                
            }
        else if(foodState==2)  //food state 2 is to draw unhappy fish
            {
                  //draw sad fish
                push();
                fill(255,0,0);
                translate(this.x,this.y,this.z);
                rotateX(this.rotateX);
                rotateY(this.rotateY);
                rotateZ(this.rotateZ);
                //rotate(this.rotateX,this.rotateY,this.rotateZ);
                //ambientMaterial(0,0,255);
                normalMaterial();
                if(fishType==1)
                    {
                    texture(fishMatSad1);  //food state 2 is to draw unhappy fish
                    model(fish1);
                    }
                else{
                   texture(fishMatSad2); 
                   model(fish2); 
                }
                pop();
                
            }
        else if(foodState==3)
            { //food state 3 is to draw dead fish
                //draw dead fish
                push();
                fill(255,0,0);
                translate(this.x,this.y,this.z);
                rotateX(this.rotateX);
                rotateY(this.rotateY);
                rotateZ(this.rotateZ);
                //rotate(this.rotateX,this.rotateY,this.rotateZ);
                ambientMaterial(255,0,0);
                if(fishType==1)
                    {
                    texture(fishMatSad1);
                    model(fish1);
                    }
                else{
                   texture(fishMatSad2);
                   model(fish2); 
                }
                pop();
              
            }
    }
    
    this.move= function()
    
   { 
        //move fish across the aquarium only if it is alive
        if(this.isAlive== true)
            {
        if(this.x >= width/2 || this.x<= -width/2)
            {
                this.speedX = -this.speedX;
                for (var i=0;i<180;i++){
                    this.rotateY = this.rotateY+1;
                }
                
            }
        
        if(this.y >= height/2 - statusBarHeight || this.y<= -height/2+statusBarHeight)
            {
                this.speedY = -this.speedY;
            }
        if(this.z >= -30 || this.z<= -500)
            {
                this.speedZ = -this.speedZ;
            }
        this.x = this.x+ this.speedX;
        this.y = this.y+ this.speedY;
        this.z = this.z+this.speedZ;
            }
        else //move fish to the top if it is dead!
            {
                this.rotateX = 0;
                this.y = -height/2 + statusBarHeight + 50 + (5*noise(random(0,3.3))); //slightly hovers the fish in y direction
                this.speedX = (noise(random(-3.3,3.3)))/1000;  // slightly moves the fish in x direction
                this.x = this.x + this.speedX;
                if(this.x >= width/2 || this.x<= -width/2)  
                {
                    this.speedX = -this.speedX;  //reverse speed direction if aquarium's limit is reached
                }
                
            }
        
    }
    
    //functions to update the mood of fish according to the time elapsed
    this.setHappy = function(){
      //  if(){
           this.foodState = 1;
        //}
    }
    this.setSad = function(){
        this.foodState = 2;
    }
    this.setDead= function(){
        this.foodState =3;
        this.isAlive=false;
    }
    //returns true if the fish is dead and has been pressed by user 
    this.removeFish = function(){
        if(this.isAlive==false)
            {  //check collision of mouse location with fish
            if(mouseIsPressed && mouseX < this.x+200+(width/2) && mouseX > this.x-200+(width/2))
                {
                    if(mouseY < this.y + 150+(height/2) && mouseY > this.y - 150+ (height/2)){
                        console.log('you removed the fish');
                        return true;
                    }
                }
            }
    
    }
     
}


///////////////////////Environment////////////////////////////
//Environment Class for drawing the aquarium
///////////////////////Environment////////////////////////////
function Environment()
{
    this.howDirty= 1;  //1 means it is clean, 2 means it is slightly dirty, 3 means it is very dirty
    this.r=255;  //for now dirty changes color of the environment 
    this.g=255;
    this.b=255;
    this.a=30;
    //function to draw the tank
    this.displayTank = function()
    {
        push();
        fill(color(this.r,this.g,this.b,this.a));
        stroke(255,100);
        quad(width/3-width/2,height-height*2/3-height/2,width*2/3-width/2,height-height*2/3-height/2,width*2/3-width/2,height-height/6-height/2,width/3-width/2,height-height/6-height/2); //back plane
        quad(-width/2,height-height/2,width/3-width/2,height-height/6-height/2,width*2/3-width/2,height-height/6-height/2,width-width/2,height-height/2); //bottom plane
        quad(-width/2,-height/2,width/3-width/2,height-height*2/3-height/2,width*2/3-width/2,height-height*2/3-height/2,width-width/2,-height/2);//top plane  
        quad(-width/2,-height/2,width/3-width/2,height-height*2/3-height/2,width/3-width/2,height-height/6-height/2,-width/2,height-height/2); //left plane
        quad(width-width/2,-height/2,width*2/3-width/2,height-height*2/3-height/2,width*2/3-width/2,height-height/6-height/2,width-width/2,height-height/2); //right plane
        pop();
    }
    //function to  make the tank dirty according to the given intensity
    this.makeDirty = function(intensity)
    {
        this.howDirty= intensity;
        if(this.howDirty==1)
            {
                this.r=255;
                this.g=255;
                this.b=255;
                this.a=30;
            }
        else if(this.howDirty==2)
            {
                this.r=135;
                this.g=191;
                this.b=209;
                this.a=200;
            }
        else if(this.howDirty==3)
            {
                this.r=97;
                this.g=145;
                this.b=160;
                this.a=200;
            }
    }
}

/////////////////////////UI elements////////////////////////
//display status bar at top and buttons at the bottom of the screen
//manage messages and confirmation screen
/////////////////////////UI elements////////////////////////
function StatusBar()
{
    this.buttonShop =createButton('Shop');
    this.buttonFood= createButton('Food');
    this.buttonClean= createButton('Clean');
    
    this.display= function()  //display the status bar at the top
    {
		textSize(18);
        push();
        fill(40, 237, 145,255);
        noStroke();
        rect(-width/2,-height/2,width,statusBarHeight);
        pop();
        var paddingX=40;
        var paddingY=60;
        var boxWidth= 200;
        fill(255);
        text("Fish Count: "+ fishCount,-width/2+paddingX, -height/2+paddingY);
        
        text("Coins: "+ coins, -width/2+2*paddingX+200, -height/2+paddingY);
        //status bar to determine happiness
        text("Happiness", -width/2+4*paddingX+350, -height/2+paddingY);
        fill(155,155,155);
        rect(-width/2+6*paddingX+400, -height/2+paddingY-15,boxWidth, 20);
        fill(255,255,0);
        var varWidth= map(happiness,0,3,0,boxWidth);
        //fill in the bar with happiness measure
        rect(-width/2+6*paddingX+400, -height/2+paddingY-15,varWidth, 20);
        //status bar to determine cleanliness
        fill(255);
        text("Cleanliness", -width/2+8*paddingX+600, -height/2+paddingY);
        fill(155,155,155);
        rect(-width/2+11*paddingX+600, -height/2+paddingY-15,boxWidth, 20);
        //fill in the bar with cleanliness measure
        fill(255,255,0);
        varWidth= map(cleanliness,0,3,0,boxWidth);
        rect(-width/2+11*paddingX+600, -height/2+paddingY-15,varWidth, 20);
    }
    //display the UI bar at the bottom
    this.displayBottomBar= function()
    {
        var paddingY= 30;
        var paddingX =30;
        fill(40, 237, 145,255);
        rect(-width/2,height/2-statusBarHeight,width,statusBarHeight);
        fill(255);
        this.buttonShop.position(paddingX,height-statusBarHeight*0.7);
        this.buttonFood.position(paddingX*2+200,height-statusBarHeight*0.7);
        this.buttonClean.position(paddingX*6+400,height-statusBarHeight*0.7);
        if(this.buttonShop.class()!="barButton")
            {
                this.buttonShop.addClass("barButton");
                this.buttonFood.addClass("barButton");
                this.buttonClean.addClass("barButton");
                var barbuttons = selectAll(".barButton");
                for (var j=0;j<barbuttons.length; j++)
                    {
                        barbuttons[j].style('font-size','18pt');
                        barbuttons[j].style('background-color','#ffdb00');
                        barbuttons[j].style('padding','10px 5px');
                        barbuttons[j].style('border-radius','10px');
                        barbuttons[j].style('font-family','ComicJens-Regular');
                        
                    }
            }
        this.buttonShop.mousePressed(this.shopBtnPressed);
        this.buttonClean.mousePressed(this.cleanBtnPressed);
        this.buttonFood.mousePressed(this.foodBtnPressed);
    }
    
   this.shopBtnPressed= function()
   {
       console.log("shop button is pressed!!");
       //update the screen drawing by entering second scene
       scene = 2;
     
       
   }
   
    this.cleanBtnPressed= function()
   {
       console.log("clean button is pressed!!");
       //Update the cleanliness factor
        if(cleanliness<3)
            {
                cleanliness+=1;
                //reset the cleanliness time to recent time
                cleanResetTime=Math.floor(Date.now()/1000);
                      if(localStorage.getItem("cleanResetTime")!= null) //
                      {
                          localStorage.setItem("cleanResetTime", cleanResetTime);
                      }
                    
            }
   }
    
     this.foodBtnPressed= function()
   {
       console.log("food button is pressed!!");
       //Update the cleanliness factor
        if(happiness<3)
            {
                happiness+=1;
                foodResetTime=Math.floor(Date.now()/1000);
                 if(localStorage.getItem("foodResetTime")!= null) //
                      {
                         localStorage.setItem("foodResetTime", foodResetTime);
                      }
                    
            }
   }
}

function Message(msg)
{
    this.msg= msg;
    this.okbtn = okButton;
   
    this.display = function()
    {
        fill(0, 220);
        stroke(0);
        strokeWeight(2);
        var originY= height/2-height/2-statusBarHeight-10;
        var originX= -width/2+400;
        var paddingX=30;
        var paddingY=30;
        rect(originX,originY,width/2,height/2-2*statusBarHeight,20);
        fill(255,255,255);
        textSize(20); 
        text(msg, originX+70,originY+2*paddingY);
        if(!this.okbtn)
            {
              this.okbtn = createButton("Ok");
                if(this.okbtn.class()!= "okButton")
                    {
                        this.okbtn.addClass("okButton");
                        this.okbtn.position(originX+width*0.75,originY+height*0.65);
                        var okbtn = select(".okButton");
                        okbtn.style('font-size','18pt');
                        okbtn.style('background-color','#ffdb00');
                        okbtn.style('padding','10px 5px');
                        okbtn.style('border-radius','10px');
                        okbtn.style('font-family','ComicJens-Regular');
                    }
            }
        this.okbtn.mousePressed(this.hideAll);
        //create a button to close the  window
    }
    
    this.showButtons = function()
    {
      shouldDisplayMsg= true; 
        if(this.okbtn)
            {
              this.okbtn.show();
            }
    }
    
    this.hideAll = function()
    {
        shouldDisplayMsg= false;
        if(this.okbtn)
            {
                this.okbtn.hide();
            }
        if(okButton)
            {
                okButton.hide();
            }
       
    }
}

function ConfirmScreen(price,index)  //index determines the fishtype
{
    this.yesBtn= yesBtn;
    this.noBtn= noBtn;
    this.price=price;
    
    this.display = function()
    {//displays a confirmation screen for purchase of fish of a given price
        fill(0, 225);
        stroke(0);
        strokeWeight(2);
        var originY= height/2-height/2-statusBarHeight-10;
        var originX= -width/2+400;
        var paddingX=30;
        var paddingY=30;
        rect(originX,originY,width/2,height*0.6-2*statusBarHeight,20);
        fill(255,255,255);
        textSize(20); 
        var confirmStr= "Are you sure you want to buy this fish for $"+ this.price;
        text(confirmStr, originX+70,originY+2*paddingY);
        
        //create, display and style an OK button
        if(!this.yesBtn)
            {
              this.yesBtn = createButton("Yes");
                if(this.yesBtn.class()!= "yesButton")
                    {
                        this.yesBtn.addClass("yesButton");
                        this.yesBtn.position(originX+width*0.65,originY+height*0.65);
                        var yesbtn = select(".yesButton");
                        yesbtn.style('font-size','18pt');
                        yesbtn.style('background-color','#ffdb00');
                        yesbtn.style('padding','10px 5px');
                        yesbtn.style('border-radius','10px');
                        yesbtn.style('font-family','ComicJens-Regular');
                    }
            }
        if(index==0)
            {
               this.yesBtn.mousePressed(shopScreen.buyFish1); 
            }
        else if(index==1)
            {
                this.yesBtn.mousePressed(shopScreen.buyFish2); 
            }
        
        //set up a no button
        if(!this.noBtn)
            {
              this.noBtn = createButton("No");
                if(this.noBtn.class()!= "noButton")
                    {
                        this.noBtn.addClass("noButton");
                        this.noBtn.position(originX+width*0.65+200,originY+height*0.65);
                        var nobtn = select(".noButton");
                        nobtn.style('font-size','18pt');
                        nobtn.style('background-color','#ffdb00');
                        nobtn.style('padding','10px 5px');
                        nobtn.style('border-radius','10px');
                        nobtn.style('font-family','ComicJens-Regular');
                    }
            }
        this.noBtn.mousePressed(this.hideAll);
        
    }
    
    
    this.hideAll = function()
    {
        //hide display screen and buttons
        shouldDisplayConfirm= false;
        if(this.yesBtn)
            {
                this.yesBtn.hide();
            }
        if(this.noBtn)
            {
                this.noBtn.hide();
            }
    }
    
}

///////////////////Shop class////////////////////////
//Functions related to shop class such as buing new fish
///////////////////Shop class////////////////////////
function Shop()
{
    this.buyBtns = buyBtns;
    this.buyBtn1= buyBtn1;
    this.buyBtn2= buyBtn2;
    this.closeButton = shopClosebtn;
    this.tempFish;
   
    this.display= function()
    {
       this.displayShopButtons(); 
       fill(0, 225);
        stroke(0);
        strokeWeight(2);
        var originY= height/4-height/2-statusBarHeight+35;
        //var originY= -height/2-statusBarHeight-10;
        var originX= -width/2+100;
        var paddingX=30;
        var paddingY=30;
        rect(originX,originY,width/2,height-2*statusBarHeight,20);
        fill(255,255,0);
        textSize(36); 
        text("Shop", originX+(width/4)-50,originY+2*paddingY);
        //create a button to close the shop window
        
        if(!shopClosebtn)
            {
            shopClosebtn = createButton('Close');
            this.closeButton= shopClosebtn;
            shopClosebtn.position(originX+width/2+width/4-40, originY+height/2+height-2*statusBarHeight-100); 
             if(shopClosebtn.class()!= "closeButton")
                  {
                    shopClosebtn.addClass("closeButton");
                    var closebuttons = select(".closeButton");
                    closebuttons.style('font-size','16pt');
                    closebuttons.style('background-color','#fff');
                    closebuttons.style('border-radius','10px');
                    closebuttons.style('font-family','ComicJens-Regular');
                  }
            }
        //close the shop if close button is pressed
        this.closeButton.mousePressed(this.closeShop);
       
        //create fish type icons, name labels and buy buttons
        for(var i=0;i<fishTypes.length;i++)
            {
                var btnWidth=170;
                var btnHeight=110;
                var paddingbx= (width/2 - 3*btnWidth)*0.25;
                var paddingby= 30;
                push();
                //draw fish icons as texture on plane
                texture(fishPics[i]);
                translate(originX+paddingbx+btnWidth*0.5 +(i*btnWidth)+i*paddingbx, originY+2*paddingY+36+paddingby+btnHeight*0.5, 0);
                plane(btnWidth,btnHeight);
                pop();
                // Draw Fish Name box
                fill(173,216,230,200);
                stroke(255);
                strokeWeight(2);
                rect(originX+paddingbx +(i*btnWidth)+i*paddingbx+btnWidth*0.1, originY+2*paddingY+36+paddingby*2+btnHeight*0.6,btnWidth*0.8, btnHeight*0.25,5);
                //write fish name
                textSize(12);
                fill(0);
                text(fishNames[i],originX+paddingbx +(i*btnWidth)+i*paddingbx+btnWidth*0.3, originY+2*paddingY+36+paddingby*2+btnHeight*0.75);
                
                //draw buy rectangle buttons
                if(totalBuyButtonCount < fishTypes.length)
                    {
                    var newbtn = createButton('Buy for $'+fishPrices[i]);
                    if(newbtn.class()!= "barButton")
                        {
                        newbtn.addClass("barButton");
                        newbtn.position(originX+width/2+paddingbx +(i*btnWidth)+i*paddingbx+btnWidth*0.1, originY+(height/2)+2*paddingY+36+paddingby*2+btnHeight);
                        var barbuttons = selectAll(".barButton");
                       
                        for (var j=0;j<barbuttons.length; j++)
                            {
                                barbuttons[j].style('font-size','18pt');
                                barbuttons[j].style('background-color','#ffdb00');
                                barbuttons[j].style('padding','10px 5px');
                                barbuttons[j].style('border-radius','10px');
                                barbuttons[j].style('font-family','ComicJens-Regular');
                                barbuttons[j].style('z-index','0');
                            }
                        }
                        totalBuyButtonCount+=1;
                        if(i==0) //update buttons according to index and check which button is pressed
                            {
                                this.buyBtn1= newbtn;
                                this.buyBtn1.mousePressed(this.confirmFish1);
                            }
                        else if(i==1)
                            {
                                this.buyBtn2= newbtn;
                                this.buyBtn2.mousePressed(this.confirmFish2);
                            }
                        this.buyBtns.push(newbtn);                      
                    }
            }  
    }
    
    this.closeShop = function()
    {
        scene=1;
        shopClosebtn.hide();
        for(var i=0;i<this.buyBtns.length; i++)
            {
                this.buyBtns[i].hide();
            }
    }
    
    this.displayShopButtons = function()
    {
         
        if(shopClosebtn)
            {
                shopClosebtn.show();
            }
        for(var i=0;i<this.buyBtns.length; i++)
            {  
                if(this.buyBtns[i])
                    {
                        this.buyBtns[i].show();
                    }
            }
    }
    
    this.confirmFish1 = function()
    {
        if( coins >= fishPrices[0]) //fish[0].fishPrice)
            {
                //buy fish 1 if price  less than coins
                confirmScreen= new ConfirmScreen(fishPrices[0],0);
                shouldDisplayConfirm = true;
                confirmScreen.display();
            }
        else
            {
                messageScreen = new Message("You do not have enough funds");
                shouldDisplayMsg = true;
                messageScreen.display();
            }  
    }
    
    this.confirmFish2 = function()
    {
         if( coins >= fishPrices[1])
            {
                //buy fish 2 if price  less than coins
                confirmScreen= new ConfirmScreen(fishPrices[1],1);
                shouldDisplayConfirm = true;
                confirmScreen.display();
            }
        else
            {
                messageScreen = new Message("You do not have enough funds");
                shouldDisplayMsg = true;
                messageScreen.display();
            }
    }
    
    this.buyFish1 = function()
    {
        //hide the confirmation screen and its buttons
        shouldDisplayConfirm = false;
        confirmScreen.hideAll();
        // Add fish 1 method is called here which increases fish count, decreases coins etc...
        console.log("fish has been added!!");
        coins = coins - fishPrices[0]; 
        fish.push(new Fish(1,1,10));  //fish type, state, price
        console.log("length of fish variable is:"+fish.length);
        fishCount = fishCount+1;    
        if(localStorage.getItem("coins")!= null) //
            {
                localStorage.setItem("coins", coins);
            }
        if(localStorage.getItem("fishCount")!= null) //
            {
                localStorage.setItem("fishCount", fishCount);
            }
        if(happiness<3)
            {
                happiness= happiness+1; //buying a new fish increases the happiness level by one
                foodResetTime=Math.floor(Date.now()/1000);
                      if(localStorage.getItem("foodResetTime")!= null) //
                      {
                          localStorage.setItem("foodResetTime", foodResetTime);
                      }
            }
        this.closeShop();
    }
    
    this.buyFish2 = function()
    {
        //hide the confirmation screen and its buttons
        shouldDisplayConfirm = false;
        confirmScreen.hideAll();
        //Add fish 2 method which increases fish count, decreases coins etc.
        coins = coins - fishPrices[1];
        fish.push(new Fish(2,1,20));
        fishCount = fishCount+1;    
        if(localStorage.getItem("fishCount")!= null) //
            {
                localStorage.setItem("fishCount", fishCount);
            } 
        if(localStorage.getItem("coins")!= null) //
            {
                localStorage.setItem("coins", coins);
            }
        if(happiness<3)
            {
                happiness= happiness+1; //buying a new fish increases the happiness level by one
                foodResetTime=Math.floor(Date.now()/1000);
                      if(localStorage.getItem("foodResetTime")!= null) //
                      {
                          localStorage.setItem("foodResetTime", foodResetTime);
                      }
            }
        this.closeShop();
        
    }
}


///////////////////Game life cycle//////////////////////
//Game lifecycle functions and other supporting functions
///////////////////Game life cycle//////////////////////
function preload()
{
  // load sound assets
    //load images
    //load models  
    fish1 = loadModel('TropicalFish01.obj');
    fish2 = loadModel('TropicalFish02.obj');
    fishMat1 = loadImage('TropicalFish01.jpg');
    fishMat2 = loadImage('TropicalFish02.jpg');
    fishMatSad1 = loadImage('TropicalFish01_sad.jpg');
    fishMatSad2 = loadImage('TropicalFish02_sad.jpg');
    //load fish icon images for shop
    fishbtn01 = loadImage('fishbtn01_hover.png');
    fishbtn02 = loadImage('fishbtn02_hover.png');
    myFont = loadFont('ComicJens-Regular.otf');
    
}

function setup() {
  createCanvas(windowWidth, windowHeight, WEBGL);
  textFont(myFont);
  textSize(18);

  totalBuyButtonCount=0;    
  scene=1;
  shopScreen = new Shop(); 
  messageScreen = new Message("");
  confirmScreen = new ConfirmScreen(0,0);
  shouldDisplayMsg = false;
  shouldDisplayConfirm = false;
  
  //cleanliness and happiness are determined from time passed
  cleanliness=3;
  happiness=3;
     
 // getting and setting time since the user started a game from local storage
    if (localStorage.getItem("usertime") === null) {
        timeSinceStart = Math.floor(Date.now()/1000); //gets the UTC timestamp in seconds
        localStorage.setItem("usertime", timeSinceStart);
   } 
    else
        {
            timeSinceStart= localStorage.getItem("usertime"); //retrieves the UTC timestamp in seconds from localstorage
        }

    //setting value of fish count from local storage
    if(localStorage.getItem("fishCount")== null)
        {
            fishCount = 0;
            localStorage.setItem("fishCount", fishCount);
        }
    else
        {
            fishCount= parseInt(localStorage.getItem("fishCount"));
        }
    
     //setting value of coins from local storage
    if(localStorage.getItem("coins")=== null)
        {
            coins = 20;
            localStorage.setItem("coins", coins);
        }
    else
        {
            coins= parseInt(localStorage.getItem("coins"));
        }
    
    // getting and setting time since the user last cleaned tank from local storage
    if (localStorage.getItem("cleanResetTime") == null) {
        cleanResetTime = Math.floor(Date.now()/1000); //gets the UTC timestamp in seconds
        localStorage.setItem("cleanResetTime", cleanResetTime);
   } 
    else
        {
            cleanResetTime = Math.floor(Date.now()/1000); //gets the UTC timestamp in seconds and updates cleanreset time
            localStorage.setItem("cleanResetTime", cleanResetTime);
            //cleanResetTime= localStorage.getItem("cleanResetTime"); //retrieves the UTC timestamp in seconds from localstorage
        }
    
    //// getting and setting time since the user last fed fish from local storage
    if (localStorage.getItem("foodResetTime") == null) {
        foodResetTime = Math.floor(Date.now()/1000); //gets the UTC timestamp in seconds
        localStorage.setItem("foodResetTime", foodResetTime);
   } 
    else
        {
            foodResetTime= localStorage.getItem("foodResetTime"); //retrieves the UTC timestamp in seconds from localstorage
        }
    // getting and setting time since the user last earned coins from local storage
    if (localStorage.getItem("coinResetTime") == null) {
        coinResetTime = Math.floor(Date.now()/1000); //gets the UTC timestamp in seconds
        localStorage.setItem("coinResetTime", coinResetTime);
   } 
    else
        {
            //coinResetTime = Math.floor(Date.now()/1000); 
           coinResetTime= localStorage.getItem("coinResetTime"); //coinTimeLimit
        }

 //function to create new fish and add a time for that fish and increase count    
 testFish = new Fish(1,1,10); //fish type, state, price
 testFish.display();
 fish.push(testFish);
 fishCount = fishCount+1;    
 testFish.fStartTime= Math.floor(Date.now()/1000); //start time
     
    if(localStorage.getItem("fishCount")!= null) //
        {
            localStorage.setItem("fishCount", fishCount);
        }
    
    console.log(fishCount);
    

    ///////FUNCTION TO ADD A SECOND FISH//////   
 testFish2 = new Fish(2,1,20); //fish type, state, price
 testFish2.display();
 fish.push(testFish2);
 fishCount = fishCount+1;    
 testFish2.fStartTime= Math.floor(Date.now()/1000); //start time
     
    if(localStorage.getItem("fishCount")!= null) //
        {
            localStorage.setItem("fishCount", fishCount);
        }
    
    console.log(fishCount);
    
    
    // add environment variable 
    environment = new Environment();
    statusBar= new StatusBar();
    
   //initialize fish types  names, images and prices
   fishNames=["Tiger Fish","Blue Tang"];
   fishPics=[fishbtn01,fishbtn02];
   fishPrices=[10,20];
    
    //Add here function to create new fish by getting fish type and number from local storage...
    
}

function draw() {
    background(173,216,230);
    angleMode(DEGREES);
    
    environment.displayTank();
    
    for (var i=0;i<fish.length;i++)
        {
            if(fish[i])
                {
                    fish[i].display();
                    fish[i].updateFish();
                    fish[i].move();
                    fish[i].removeFish();
                }
        }
   
    statusBar.display();
    statusBar.displayBottomBar(); 
    
   //text((Math.floor(Date.now()/1000))-timeSinceStart, 200,200);
    
    //change cleanliness of the tank as time progresses 
    if( Math.floor(Date.now()/1000)- cleanResetTime > cleanlinessTimeLimit   )  //frameCount%100 == 99
        {
            if(cleanliness>0)
                {
                    cleanliness=cleanliness-1;
                    cleanResetTime=Math.floor(Date.now()/1000);
                      if(localStorage.getItem("cleanResetTime")!= null) //
                      {
                          localStorage.setItem("cleanResetTime", cleanResetTime);
                      }
                    
                } 
        }
    
    //change happiness of the tank as time progresses change state of fish
    if( Math.floor(Date.now()/1000)- foodResetTime > foodTimeLimit)  //frameCount%100 == 99
        {
            if(happiness>0)
                {
                    happiness=happiness-1;
                    foodResetTime=Math.floor(Date.now()/1000);
                      if(localStorage.getItem("foodResetTime")!= null) //
                      {
                          localStorage.setItem("foodResetTime", foodResetTime);
                      }
                    
                } 
        }
    
    //change state of fish as state of happiness changes 
    for(var i=0;i<fish.length;i++)
        {
            if(happiness==0)
               {
                  fish[i].setDead();  
               }
            else if(happiness==2)
                {
                    fish[i].setSad();
                    console.log('fish is set to SAD'+ fish[i].foodState);
                }
            else{
                    fish[i].setHappy();
                }
        }
    
    removeDeadFish();
    generateCoins();
    
    //change the color of the water in the tank as cleanliness decreases
    if(cleanliness==1 || cleanliness==0)
                {
                    environment.makeDirty(3);
                }
            else if(cleanliness==2)
                {
                    environment.makeDirty(2);
                }
            else
                {
                    environment.makeDirty(1);
                }
    
    
    //display shop screen
    if(scene==2)
        {
            shopScreen.display();

        }
    if(shouldDisplayMsg==true)
        {
            messageScreen.display();
        }
    else{
        messageScreen.hideAll();
        }
    if(shouldDisplayConfirm==true)
        {
            confirmScreen.display();
        }
    else{
        confirmScreen.hideAll();
    }

}

//function to remove fish from tank if it is dead
function removeDeadFish()
{ 
    for(var i=0;i< fish.length;i++)
        {
          if(fish[i].removeFish() == true)  //this function returns true if fish is dead and has been pressed by user
              {
                  fish.splice(i,1);
                  fishCount -= 1;
              }
              
        }
}

function generateCoins()
{
 //Add coins if time passed is greater than 
    if( Math.floor(Date.now()/1000)- coinResetTime > coinTimeLimit)  //frameCount%100 == 99
        {
            coins+=20;
            coinResetTime = Math.floor(Date.now()/1000); //gets the UTC timestamp in seconds
            //moeezo add animation to coins
           // for(){
             //  text(); 
            //}
            if(localStorage.getItem("coins")!= null) 
            {
                localStorage.setItem("coins", coins);
            }
            if(localStorage.getItem("coinResetTime")!= null) 
            {
                localStorage.setItem("coinResetTime", coinResetTime);
            }
            
        }   
}
