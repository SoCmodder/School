
#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG

	#define pthread_mutex_lock( x )	\
		printf("DEBUG: entering mutex: %s[%u]\n", __FILE__, __LINE__);	\
		pthread_mutex_lock( x )

	#define pthread_mutex_unlock( x ) \
		printf("DEBUG: exiting mutex: %s[%u]\n", __FILE__, __LINE__);	\
		pthread_mutex_unlock( x )

#endif

#endif

