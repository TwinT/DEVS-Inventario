[top]
components : CA@ClientA
out : out_port
link : query_o@CA out_port

[CA]
distribution : Exponential
mean : 0.12

