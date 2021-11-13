// define Two tasks 
void Task1(void *pvParameters);
void Task2(void *pvParameters);
void Task2(void *pvParameters);
// the setup function runs once when you press reset or power the board
void setup() {
 
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
 
  // Now set up the tasks
  xTaskCreatePinnedToCore(
    Task1,            // Function to be implemented
    
    "First Task",     // Name of the Task
    
    1024,             // Stack Size
    
    NULL,             // Task Input Parameters

    2,               // Priority, with 3 being the highest, and 0 being the lowest.
    
    NULL,             // Task Handle
  
    0               // Core where the Task should run
    
    );
 
  xTaskCreatePinnedToCore(
    Task2,                // Function to be implemented
    
    "Second Task",        // Name of the Task
    
    1024,                 // Stack size
    
    NULL,                 // Task Input Parameters
    
    3,                     // Priority
    
    NULL,                  // Task Handle
    
    1                     // Core where the Task should run
    
    );


  xTaskCreatePinnedToCore(
    Task3,                // Function to be implemented
    
    "Third Task",        // Name of the Task
    
    1024,                 // Stack size
    
    NULL,                 // Task Input Parameters
    
    1,                     // Priority
    
    NULL,                  // Task Handle
    
    1                     // Core where the Task should run
    
    );    
    
// Now the task scheduler, which takes over control of scheduling individual tasks, is automaticall started.
} 
 
void loop() {
  // Empty. Things are done in Tasks.
}
 
/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/
 
void Task1(void *pvParameters)  // This is a task.
{
  (void)pvParameters;
 
 
  while (true)  // A Task shall never return or exit.
  {
    Serial.print("Inside Task 1 of Core : ");
    Serial.println(xPortGetCoreID());            
    vTaskDelay(15);        
  }
}
 
void Task2(void *pvParameters)  // This is a task.
{
  (void)pvParameters;
 
 
  while (true) {
 
    Serial.print("Inside Task 2 of Core: ");
    Serial.println(xPortGetCoreID());    
    vTaskDelay(10);  
  }
}
 

void Task3(void *pvParameters)  // This is a task.
{
  (void)pvParameters;
 
 
  while (true) {
 
    Serial.print("Inside Task 3 of Core: ");
    Serial.println(xPortGetCoreID());    
    vTaskDelay(10);  
  }
}


