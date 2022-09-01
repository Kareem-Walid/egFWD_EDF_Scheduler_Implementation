------------------------------------------------------------------------------
1
------------------------------------------------------------------------------


/*
 * -----------------------------------------------------------
 * The Idle task.
 * ----------------------------------------------------------
 *
 * The portTASK_FUNCTION() macro is used to allow port/compiler specific
 * language extensions.  The equivalent prototype for this function is:
 *
 * void prvIdleTask( void *pvParameters );
 *
 */
static portTASK_FUNCTION( prvIdleTask, pvParameters )
{
                ......
    for( ; ; )
    {
		#if( configUSE_EDF_SCHEDULER == 1)
		{
			/*E.C. Modify the idle task to keep it always the farest deadline*/
			listSET_LIST_ITEM_VALUE( &( ( pxCurrentTCB )->xStateListItem ), ( pxCurrentTCB )->xTaskPeriod + xTaskGetTickCount() );
			listINSERT_END( &(xReadyTasksListEDF), &( ( pxCurrentTCB )->xStateListItem ) );
		}
		#endif

------------------------------------------------------------------------------
2
------------------------------------------------------------------------------

BaseType_t xTaskIncrementTick( void )
{
     
	 ..............

    if( uxSchedulerSuspended == ( UBaseType_t ) pdFALSE )
    {

        ........

        if( xConstTickCount == ( TickType_t ) 0U ) /*lint !e774 'if' does not always evaluate to false as it is looking for an overflow. */
        {
            .......
        }
        else
        {
            ........
        }
 
 
           .........
		   
        if( xConstTickCount >= xNextTaskUnblockTime )
        {
            for( ; ; )
            {
                if( listLIST_IS_EMPTY( pxDelayedTaskList ) != pdFALSE )
                {
                   
				   ................
                }
                else
                {
                   .......
                    if( xConstTickCount < xItemValue )
                    {
                       ........
                    }
                    else
                    {
                        .......
                    }

                 ........
				 ........
				 ........
                    if( listLIST_ITEM_CONTAINER( &( pxTCB->xEventListItem ) ) != NULL )
                    {
                        ...
                    }
                    else
                    {
                       .....
                    }

					/*E.C. Missing Changes (2) : Calculate New Deadline*/
					#if (configUSE_EDF_SCHEDULER == 1)
						listSET_LIST_ITEM_VALUE( &( ( pxTCB )->xStateListItem ), ( pxTCB)->xTaskPeriod + xTaskGetTickCount() );
					#endif
					
                    /* Place the unblocked task into the appropriate ready
                     * list. */
                    prvAddTaskToReadyList( pxTCB );
					
					/*E.C. Missing Changes: Context Switching will always take place 
					 *to always restore task with earlist deadline at head of EDF RL */
					#if (configUSE_EDF_SCHEDULER == 1)
						xSwitchRequired = pdTRUE;
					#endif
					
					
					.............
                }
            }
        }
	}
}

