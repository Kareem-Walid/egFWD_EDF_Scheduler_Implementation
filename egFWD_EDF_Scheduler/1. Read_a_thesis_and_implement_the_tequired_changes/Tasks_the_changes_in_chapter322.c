


// 1st 
/*-----------------------------------------------------------*/
/************* EDF SCHEDULAR  *************/
/* E.C. : the new RedyList */
#if ( configUSE_EDF_SCHEDULER == 1 )
PRIVILEGED_DATA static List_t xReadyTasksListEDF;        /*< Ready tasks orderedby their deadline. */
#endif
		
 /* ------------------------- */ 
 
 
 
// 2nd
 
 static void prvInitialiseTaskLists( void )
{
	
	.......
	
	/* ----------------------- */ 
	/* E.C. */
	#if ( configUSE_EDF_SCHEDULER == 1 )
	{
		vListInitialise( &xReadyTasksListEDF );
	}
	#endif
	/* ------------------------------- */
	
	.....
	
}


// 3rd

/*
 * Place the task represented by pxTCB into the appropriate ready list for
 * the task.  It is inserted at the end of the list.
 */
/*  E.C. : */
#if configUSE_EDF_SCHEDULER == 0		
	#define prvAddTaskToReadyList( pxTCB )                                                                 \
		traceMOVED_TASK_TO_READY_STATE( pxTCB );                                                           \
		taskRECORD_READY_PRIORITY( ( pxTCB )->uxPriority );                                                \
		listINSERT_END( &( pxReadyTasksLists[ ( pxTCB )->uxPriority ] ), &( ( pxTCB )->xStateListItem ) ); \
		tracePOST_MOVED_TASK_TO_READY_STATE( pxTCB )
#else
	#define prvAddTaskToReadyList( pxTCB ) /*xGenericListIteam must contain thedeadline value */ \
	traceMOVED_TASK_TO_READY_STATE(pxTCB);														 \
	vListInsert( &(xReadyTasksListEDF), &( ( pxTCB )->xStateListItem ) );						 

#endif




// 4th
/* E.C. : the period of a task */
#if ( configUSE_EDF_SCHEDULER == 1 )
	TickType_t xTaskPeriod; /*< Stores the period in tick of the task. > */
#endif





// 5th
BaseType_t xTaskPeriodicCreate( TaskFunction_t pxTaskCode,
                            const char * const pcName, /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                            const configSTACK_DEPTH_TYPE usStackDepth,
                            void * const pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t * const pxCreatedTask,
							TickType_t period )
				
				{

/*E.C. : initialize the period */
			pxNewTCB->xTaskPeriod = period;
			
			
		................	
			
if( pxNewTCB != NULL )
        {
            #if ( tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE != 0 ) /*lint !e9029 !e731 Macro has been consolidated for readability reasons. */
                {
                    ......................................
                }
            #endif /* tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE */

                 ..................
					
			/*E.C. : initialize the period */
			pxNewTCB->xTaskPeriod = period;
			/*E.C. : insert the period value in the generic list iteam before to add the task in RL: */
			listSET_LIST_ITEM_VALUE( &( ( pxNewTCB )->xStateListItem ), ( pxNewTCB )->xTaskPeriod + xTaskGetTickCount() );		

                 ...............
		}
		
		
		
		
// 7th
void vTaskStartScheduler( void )
{
    
	.........
	 #if ( configSUPPORT_STATIC_ALLOCATION == 1 )
	 {
		 ...............
	 }

    #else /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
        {
			/*E.C. : */
			#if (configUSE_EDF_SCHEDULER == 1)
			{
				TickType_t initIDLEPeriod = 300;
				xReturn = xTaskPeriodicCreate( 	prvIdleTask,
												"IDLE",
												configMINIMAL_STACK_SIZE, 
												(void * ) NULL, 
												portPRIVILEGE_BIT,
												&xIdleTaskHandle,
												initIDLEPeriod );
			}
			#else
            {
				/* The Idle task is being created using dynamically allocated RAM. */
				xReturn = xTaskCreate( prvIdleTask,
									   configIDLE_TASK_NAME,
									   configMINIMAL_STACK_SIZE,
									   ( void * ) NULL,
									   portPRIVILEGE_BIT,  /* In effect ( tskIDLE_PRIORITY | portPRIVILEGE_BIT ), but tskIDLE_PRIORITY is zero. */
									   &xIdleTaskHandle ); /*lint !e961 MISRA exception, justified as it is not a redundant explicit cast to all supported compilers. */
			}
			#endif
			
		................................
		
}




// 8th

void vTaskSwitchContext( void )
{
	
	
	.............. 
	
	
/* --------------------------- */
        /* E.C. : */
		#if (configUSE_EDF_SCHEDULER == 0)
		{
			taskSELECT_HIGHEST_PRIORITY_TASK(); /*lint !e9079 void * is used as this macro is used with timers and co-routines too.  Alignment is known to be fine as the type of the pointer stored and retrieved is the same. */
			traceTASK_SWITCHED_IN();			
		}
		#else
		{
			pxCurrentTCB = (TCB_t * ) listGET_OWNER_OF_HEAD_ENTRY( &(xReadyTasksListEDF ) );
			traceTASK_SWITCHED_IN();			
		}
		#endif
		/* --------------------------- */
		
		....
		
}


/*-----------------------------------------------------------*/