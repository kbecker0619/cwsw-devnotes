This abstraction "lives" in the Services layer. It requires a 1-ms tic - either the timer interrupt ISR must call into our "ticker", or else it must be in a 1-ms task.
