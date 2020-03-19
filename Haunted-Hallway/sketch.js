//Haunted Hallway: Halloween themed Game 
//Move player up and down with mouse to Navigate the haunted hallway and avoid all ghosts
var back;
var myPlayer;
var ghostTypes=['casper','ogre','pumpkin']; //array holds ghost types
var positionY;
var ghosts= []; //array to hold ghosts
var openLane; //flag to check if a new ghost can be placed on an open lane
var bloodDrops =[]; //array to hold blood drops
var numBloodDrops = 25;  //number of blood drops to add
var scene;
var ghostIndex;   //index of the collided ghost
var count; //to count the number of blood droplets made
var gameStartTime;
var gameDuration = 60; //duration of the game in seconds

var timeofCollision = 0; //save the time of collision in seconds

function Background(){
    this.x = width/2;
    this.y= height/2;  
    this.numTeeth = 28;
    this.triangleWidth= width/this.numTeeth;
    this.speedX= this.triangleWidth*0.1;
    //getter and setter functions for speed and triangle width
    this.getTriangleWidth= function(){
        return this.triangleWidth;
    }
    this.setSpeedX= function(xVal){
        this.speedX=xVal;
    }
    this.getSpeedX= function(){
        return this.speedX;
    }
    this.drawBackground = function(){
        push();
        noStroke();
        fill(40);
        rect(this.x,this.y-(height/3),width+this.triangleWidth*2,height/3);
        fill(60);
        rect(this.x,this.y,width+this.triangleWidth*2,height/3);
        fill(40);
        rect(this.x,this.y+(height/3),width+this.triangleWidth*2, height/3);
        fill(255,0,0,100);
        
        for(var j=floor(this.x-(width*0.5)); j< width; j+=this.triangleWidth)
            {
               triangle(j,0,j+this.triangleWidth,0,j+(this.triangleWidth/2),25);
               triangle(j,height,j+this.triangleWidth,height,j+(this.triangleWidth/2),height-25);
            }
        pop(); 
    }
    
    this.backMove= function(){
        this.x= this.x-this.speedX;
        if (this.x <= (width*0.5)-this.triangleWidth) 
            {
                this.x= width/2;
            }
    }

}

function Player()
{
    //player properties
    this.posX= width*0.15;
    this.posY= height/2;
    this.speedX = 0;
    this.speedY=0.1;
    this.sizeX=70;
    this.sizeY=70;
    this.acolor= 255;
    this.color=color(252, 224, 239,this.acolor);
    this.isDead= false;
    this.hasCollided= false;
    this.rotate=0;
    
    //player methods
    this.display= function(){
        push();
        noStroke();
        fill(this.color);
        translate(this.posX,this.posY);
        rotate(this.rotate);
        arc(0,0,this.sizeX,this.sizeY,PI/6,(2*PI)-PI/20,PIE);
        fill(252, 153, 206);
        triangle(0,-this.sizeY*0.5,-20,0-(this.sizeY*0.5)-10,-20,-(this.sizeY*0.5)+10);
        triangle(0,-this.sizeY*0.5,+20,0-(this.sizeY*0.5)-10,+20,-(this.sizeY*0.5)+10);
        fill(0);
        ellipse(0+this.sizeX*0.25,0-this.sizeY*0.2,10,15);
        pop();
    }
    this.move= function(){
        
       if(mouseY < 30){ //check for upperbound and stop player from going outside the game area
           this.posY= 30+(this.sizeY/2);
           this.speedY=0;
           }
        
        if(mouseY > height-30){ //check for lowerbound and stop playe from going outside the game area
            this.posY= height-30 -(this.sizeY/2);
            this.speedY=0;
        }
            
        if(mouseY > 30 && mouseY < height-30)  //move player's Y coordinate according to mouseY position
        {
            this.speedY= (mouseY - this.posY) * 0.1;
            this.posY+=this.speedY;
            
        }  
    }
    
    this.getBoundingBox=function(){
        var boundingBox= [this.posX, this.posY,this.sizeX,this.sizeY];
        return boundingBox;
    }
    
    this.checkCollision= function(rect){ //the bouding box is adjusted a little
        if (this.posX-(this.sizeX*0.25) < rect.posX + (rect.sizeX*0.5) &&
            this.posX+(this.sizeX*0.25) > rect.posX-(rect.sizeX*0.5) &&
            this.posY+(this.sizeY*0.35) > rect.posY-(rect.sizeY*0.5) &&
            this.posY - (this.sizeY*0.45) < rect.posY + (rect.sizeY*0.5)) 
        {
            this.hasCollided = true;
            this.isDead = true;
        }
    }
    
    this.spinOut= function(){
        
        if(this.rotate < 2*PI)
        {
            this.rotate+=0.15;
        }
        if(this.acolor > 50)
        {
            this.acolor-= 5;
            this.color = color(252, 224, 239,this.acolor);    
        }
        //add blood to the scene
       if(count < numBloodDrops)
           {
             bloodDrops.push(new BloodDroplet(this.posX+this.sizeX*0.5,this.posY)); 
             count+=1;   
           }
    };
    
    this.fadeOut= function(){
        if(this.acolor > 20)
        {
            this.acolor-= 1;
            this.color = color(252, 224, 239,this.acolor);    
        }
    };
}


function Ghost(type,posY)
{
    //Ghost properties 
    this.posX= width+ 200;
    this.posY= posY;
    this.speedX = 5;
    this.speedY=0;
    this.sizeX=70;
    this.sizeY=70;
    this.scale=1;
    this.acolor=255;
    this.color=color(200,200,200,this.acolor);
    this.type= type;
    this.isOut = false; //this will be set to true if ghost has moved out of the screen so that ghost can be removed from the game
    this.hasCollided= false;
    this.display= function(){ 
        push();
        scale(this.scale);
        if(this.type== 'casper')
            {
        noStroke();        
        fill(this.color);
        this.sizeY= (height-60)* 0.5;        
        ellipse(this.posX,this.posY-((this.sizeY*0.5)-(2*this.sizeY/3)*0.5),this.sizeX, this.sizeY*2/3);
        rect(this.posX,this.posY,this.sizeX,(this.sizeY/3));
        beginShape();
                curveVertex(this.posX-this.sizeX*0.5,this.posY+this.sizeY*0.5-(this.sizeY/3));
                curveVertex(this.posX-this.sizeX*0.5,this.posY+this.sizeY*0.5);
                curveVertex(this.posX-this.sizeX*0.3,this.posY+this.sizeY*0.5-(this.sizeY/3));
                curveVertex(this.posX,this.posY+this.sizeY*0.5);
                curveVertex(this.posX+this.sizeX*0.3,this.posY+this.sizeY*0.5-(this.sizeY/3));
                curveVertex(this.posX+this.sizeX*0.5,this.posY+this.sizeY*0.5);
                curveVertex(this.posX+this.sizeX*0.5,this.posY+this.sizeY*0.5-(this.sizeY/3));
                curveVertex(this.posX-this.sizeX*0.5,this.posY+this.sizeY*0.5-(this.sizeY/3));
        endShape(CLOSE); 
        noFill();
        strokeWeight(2);
        stroke(255,0,0);
          //draw ghost's mouth
        beginShape();
                vertex(this.posX-this.sizeX*0.35,this.posY-this.sizeY*0.1-15);
                vertex(this.posX-this.sizeX*0.35,this.posY-this.sizeY*0.1);
                vertex(this.posX-this.sizeX*0.15,this.posY-this.sizeY*0.1-15);
                vertex(this.posX,this.posY-this.sizeY*0.1);
                vertex(this.posX+this.sizeX*0.15,this.posY-this.sizeY*0.1-15);
                vertex(this.posX+this.sizeX*0.35,this.posY-this.sizeY*0.1);
                vertex(this.posX+this.sizeX*0.35,this.posY-this.sizeY*0.1-15);
        endShape(); 
         //draw eyes
        fill(0);
        ellipse(this.posX-this.sizeX*0.2,this.posY-this.sizeY*0.3,20,30);
        ellipse(this.posX+this.sizeX*0.2,this.posY-this.sizeY*0.3,20,30);
        fill(255);
        noStroke();
        ellipse(this.posX-this.sizeX*0.2,this.posY-this.sizeY*0.3,15,20);
        ellipse(this.posX+this.sizeX*0.2,this.posY-this.sizeY*0.3,15,20); 
        
            }
        else if(this.type== 'ogre')
            {
                noStroke();
                this.color=color(68, 200, 78,this.acolor);
                fill(this.color);
                this.sizeY= (height-60)* 0.25;
                ellipse(this.posX,this.posY,this.sizeX,this.sizeY);
                ellipse(this.posX-this.sizeX*0.4,this.posY+this.sizeY*0.5-10, this.sizeX*0.8,this.sizeY*0.4);
                ellipse(this.posX+this.sizeX*0.4,this.posY+this.sizeY*0.5-10, this.sizeX*0.8,this.sizeY*0.4);
                ellipse(this.posX-this.sizeX*0.45,this.posY,this.sizeX*0.8,this.sizeY*0.7);
                noFill();
                stroke(0);
                //mouth
                beginShape();
                vertex(this.posX-this.sizeX*0.65,this.posY+this.sizeY*0.3-15);
                vertex(this.posX-this.sizeX*0.55,this.posY+this.sizeY*0.3);
                vertex(this.posX-this.sizeX*0.35,this.posY+this.sizeY*0.3-15);
                vertex(this.posX-this.sizeX*0.15,this.posY+this.sizeY*0.3);
                vertex(this.posX,this.posY+this.sizeY*0.3-15);
                vertex(this.posX+this.sizeX*0.15,this.posY+this.sizeY*0.3);
                vertex(this.posX+this.sizeX*0.15,this.posY+this.sizeY*0.3-15);
                endShape();
                fill(0);
                stroke(255,0,0);
                 fill(0);
                ellipse(this.posX-this.sizeX*0.2,this.posY-this.sizeY*0.3,20,30);
                fill(255);
                noStroke();
                ellipse(this.posX-this.sizeX*0.2,this.posY-this.sizeY*0.3,15,20); 
                
            }
        else if(this.type=='pumpkin')
            {
                this.sizeX=100;
                this.sizeY= (height-60)* 0.25;
                this.color=color(252, 177, 27, this.acolor);
                stroke(100);
                strokeWeight(1);
                fill(this.color);
                
                ellipse(this.posX,this.posY,this.sizeX/3,this.sizeY);
                ellipse(this.posX-(this.sizeX/3)*0.85,this.posY,this.sizeX/3,this.sizeY*0.95);
                ellipse(this.posX+(this.sizeX/3)*0.85,this.posY,this.sizeX/3,this.sizeY*0.95);
                //mouth
                noFill();
                stroke(0);
                beginShape();
                vertex(this.posX-this.sizeX*0.35,this.posY+this.sizeY*0.15-15);
                vertex(this.posX-this.sizeX*0.35,this.posY+this.sizeY*0.15);
                vertex(this.posX-this.sizeX*0.15,this.posY+this.sizeY*0.15-15);
                vertex(this.posX,this.posY+this.sizeY*0.15);
                vertex(this.posX+this.sizeX*0.15,this.posY+this.sizeY*0.15-15);
                vertex(this.posX+this.sizeX*0.35,this.posY+this.sizeY*0.15);
                vertex(this.posX+this.sizeX*0.35,this.posY+this.sizeY*0.15-15);
                endShape();
                //eyes
                fill(0);
                ellipse(this.posX-this.sizeX*0.2,this.posY-this.sizeY*0.3,20,30);
                ellipse(this.posX+this.sizeX*0.2,this.posY-this.sizeY*0.3,20,30);
                fill(255);
                noStroke();
                ellipse(this.posX-this.sizeX*0.2,this.posY-this.sizeY*0.3,15,20);
                ellipse(this.posX+this.sizeX*0.2,this.posY-this.sizeY*0.3,15,20);   
            }
        pop();
    };
    
    //makes the ghost move horizontally
    this.move= function(){
        this.posX -= this.speedX;
    };
    
    //returns the ghost's bounding box
    this.getBoundingBox=function(){
        var boundingBox= [this.posX, this.posY,this.sizeX,this.sizeY];
        return boundingBox;
    };
    
    //method to check collision of ghost with another object of either player or ghost type
    this.checkCollision= function(rect){
           if (this.posX-(this.sizeX*0.5) < rect.posX + (rect.sizeX*0.5) &&
            this.posX+(this.sizeX*0.5) > rect.posX-(rect.sizeX*0.5) &&
            this.posY+(this.sizeY*0.5) > rect.posY-(rect.sizeY*0.5) &&
            this.posY - (this.sizeY*0.5) < rect.posY + (rect.sizeY*0.5)) 
        {
            this.hasCollided = true;
        }
    };
    
    //function to check ghost's collision with a rect array that contains 4 values x,y,sizeX and sizeY
    this.checkRectCollision= function(rect){   
           if (this.posX-(this.sizeX*0.5) < rect[0] + (rect[2]*0.5) &&
            this.posX+(this.sizeX*0.5) > rect[0]-(rect[2]*0.5) &&
            this.posY+(this.sizeY*0.5) > rect[1]-(rect[3]*0.5) &&
            this.posY - (this.sizeY*0.5) < rect[1] + (rect[3]*0.5)) 
        {
            return true;
        }
    };
    
    //returns true if ghost has moved out of the screen
    this.hasGhostMovedOut= function(){
        if(this.posX+this.sizeX < 0)
            {
                this.isOut = true;
                return this.isOut;
            }
    };
    
    //scales up the ghost
    this.scaleUp= function() 
    {
        if(this.scale < 1.2)
            {
                this.scale= this.scale+ 0.02;
            }
    };
    
    //make the ghosts disappear
    this.fadeOut= function(){
        if(this.acolor > 0)
        {
            this.acolor-= 3;
            this.color = color(252, 224, 239,this.acolor);    
        }
    };
}

function BloodDroplet(posX,posY)
{
  this.acceleration = createVector(0, 0.05);
  this.velocity = createVector(random(-1, 1), random(-1, 0));
  this.position = createVector(posX,posY);
  this.lifespan = 255.0;
  //method to draw a blood droplet
  this.display = function (){
    noStroke();
    fill(255,0,0, this.lifespan);
    ellipse(this.position.x, this.position.y, 12, 15);
  };  
  //method to animate the blooddrops    
  this.move = function(){
    this.velocity.add(this.acceleration);
    this.position.add(this.velocity);
    this.lifespan -= 2;
  }; 

// method to check if blood should still be displayed
  this.hasDried = function()
  {
        if (this.lifespan < 0) {
            return true;
        } 
        else {
            return false;
      }  
  };
  
}

function addGhosts()
{ 
//Adds ghosts to the game at random intervals, provides a random type and y position for the ghosts
var sizeY= (height-60)* 0.5; 
var ghostPos1=[height/3,height/5,height+height/3];
var gPosY= [height/3-((height-60)*0.15), height/2, height-(height/3)+((height-60)*0.15)]; //three possible y positions for smaller ghost types
var gPosY2= [height-30-sizeY*0.5, 30+(sizeY*0.5)];  //two possible y positions for larger ghost type
//variables for bounding box of the newly generated ghost
var gPosX= width+200;
var gSizeX= 200;
var gSizeY= (height-60)*0.55;//(height-60)*0.25;
 openLane = true;
    
    var gtype = ghostTypes[floor(random(3))];
    if(gtype=='casper')
        {
            positionY = gPosY2[floor(random(2))];
            gSizeY= (height-60)*0.85;//(height-60)*0.5;
        }
    else
        {
           positionY = gPosY[floor(random(3))]; 
        }
var gboundingbox =[gPosX,positionY,gSizeX,gSizeY]; //bounding box of the new ghost to be added 
    //check collision of new ghost's bounding box against all possible ghosts if true, turn openLane to false
    for (var i=0;i<ghosts.length;i++)
        {
            if(ghosts[i].checkRectCollision(gboundingbox) == true)
                {   
                    openLane= false;  //if new ghost collides with a previous ghost don't draw it
                }
        }
    
     if(frameCount%int(random(70,110))==0 && openLane==true){ //create some ghosts at random intervals and add to the ghosts array 
                
                ghosts.push(new Ghost(gtype,positionY));
            }
    
     for(var k=0;k<ghosts.length;k++)
        {
            ghosts[k].display();
            ghosts[k].move();
        }

}

function checkForAllCollisions(){
         for(var k=0;k<ghosts.length;k++)
        {
            myPlayer.checkCollision(ghosts[k]);
            
            if (myPlayer.hasCollided == true){
                ghosts[k].hasCollided = true;
                ghosts[k].scaleUp();
                myPlayer.spinOut();
                scene = 2;
                console.log('collided with ghost number'+ k);
                ghostIndex = k;
                timeofCollision = millis()/1000;
                console.log('time of collsion is '+ timeofCollision);
                break;
            }
            
             if(ghosts[k].hasGhostMovedOut()== true)
           {
              ghosts.splice(k,1);  //remove the ghost from the array if it moves out of the screen
           }
        }
}

function speedUpGame(){
    //display time passed
    fill(255);
    textSize(20);
    text('Time remaining:  ' + (gameDuration - int(millis()/1000 - gameStartTime)), width*0.5, height*0.95);
    
    if((millis()-(gameStartTime*1000)) > (gameDuration*0.45*1000) && (millis()-(gameStartTime*1000)) < (gameDuration*0.52*1000))
       {
           fill(255,255,0,150);
           textSize(20);
           text('SPEEDING UP!', width*0.5, height*0.1);
       }
    
    if( (millis()-(gameStartTime*1000)) > gameDuration*0.5*1000)  //speed up ghosts after 30 seconds of starting the game
    {
        for (var i=0;i<ghosts.length;i++)
            {
              ghosts[i].speedX = 10;
            }
    }
}

function checkForGameWin(){
    if( (millis()-(gameStartTime*1000)) > gameDuration*1000)  //speed up ghosts after 30 seconds of starting the game
    {
        scene= 3;
    }
}
function setup() {
  //create canvas in the middle of the screen
  var canvasWidth = windowWidth*0.8;
  console.log('width of canvas'+canvasWidth);
  var canvasHeight= 400;
  var cnv = createCanvas(canvasWidth, canvasHeight);
  var winx = (windowWidth - width) / 2;
  var winy = (windowHeight - height) / 2;
  //cnv.position(winx, winy);
  ellipseMode(CENTER);
  rectMode(CENTER);
  textAlign(CENTER);
  var timePassedn; //this is used in game win scenario to keep track of time
    
  gameStartTime = (millis()/1000);
  count =0;
  scene=1;
  ghostIndex = -1; //no collision has taken place
  back = new Background();
  myPlayer= new Player();
    
}


function draw() {
 
    background(255, 217, 179);
    
    	switch (scene) {
		case 1: 
			back.drawBackground();
            back.backMove();
            addGhosts();  
            myPlayer.display();
            myPlayer.move();
            checkForAllCollisions();
            speedUpGame();
            checkForGameWin();
			break;
		case 2: //lose scenario
            back.drawBackground();
			
            for(var k=0;k<ghosts.length;k++)
              {
                ghosts[k].display();
                //ghosts[k].move();
              }
            ghosts[ghostIndex].scaleUp(); //the collided ghost increases in size after collision 
            ghosts[ghostIndex].move(); //the collided ghost continues to move
            myPlayer.display();    
            myPlayer.spinOut();
            for(var i=0;i<bloodDrops.length;i++)
               {
                 bloodDrops[i].display();
                 bloodDrops[i].move();
                 if(bloodDrops[i].hasDried()== true)
                     {
                        bloodDrops.splice(i,1);
                     }
               }
             var timePassed= (millis()/1000) - timeofCollision;     
             if( timePassed < 5)
                   {
                      fill(255,255,0);
                      textSize(25);
                      text('Game Over!', width*0.5, height*0.3); 
                   }
                else{
                    textSize(22);
                    text('Press any key to restart', width*0.5, height*0.3); 
                }
              if(timePassed > 3 && timePassed < 20)
                    {
                       textSize(20);
                       text('May Your Soul Rest in Peace...', width*0.5, height*0.5); 
                    }
			break;
        case 3: //win scenario
            back.drawBackground();
            myPlayer.display();
                for(var k=0;k<ghosts.length;k++)
                {
                        ghosts[k].display();
                        ghosts[k].fadeOut();
                }
            timePassedn =  (millis()/1000)- gameDuration- gameStartTime;
            console.log('value of time passed is'+ timePassedn);    
            if( timePassedn > 1)
                   {
                      fill(255,255,0);
                      textSize(25);
                      text('Congratulations!', width*0.5, height*0.3); 
                   }
            if(timePassedn > 2 && timePassedn < 6){
                    textSize(22);
                    text("You made it through the Hallway", width*0.5, height*0.5); 
                }
            else if(timePassedn>= 6)
                    {
                    textSize(27);
                    text("Mu ha ha ha!", width*0.5, height*0.5);
                    myPlayer.fadeOut(); 
                    }
                if(timePassedn > 4){
                    textSize(22);
                    text("Welcome to the land of the Dead!", width*0.5, height*0.65); 
                } 
                if(timePassedn > 6){
                    textSize(22);
                    text("Press any key to restart", width*0.5, height*0.75); 
                } 
            break;    

	}  
	
}

function keyPressed() {
    //reset all variables to restart the Game
    if(scene== 2 || scene==3)
        {
          count =0;
          scene=1;
          ghostIndex = -1; //no collision has taken place
          timeofCollision = 0;
          openLane = true;
          myPlayer.isDead= false;
          myPlayer.hasCollided= false;
          myPlayer.rotate = 0;
          myPlayer.acolor= 255;
          myPlayer.color=color(252, 224, 239,255);    
          ghosts = [];
          gameStartTime = (millis()/1000);
        }
    
}