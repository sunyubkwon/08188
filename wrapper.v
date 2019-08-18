`timescale 1ns / 1ps

module wrapper #(

        parameter READ_LATENCY = 3,
        parameter ADDR_WIDTH = 15,
        parameter DATA_WIDTH = 31  
        )(
        input wire clk_a,
		input wire arstz_aq,
		input wire [ADDR_WIDTH-1 : 0] addr,
		input wire en,
		input wire we,
		input wire [DATA_WIDTH-1 : 0] din,
		output wire [DATA_WIDTH-1 : 0] dout,
		output wire valid
        );
        reg [2:0] wait_counter;
        reg [2:0] wait_counter_next;
        reg en_to_blkmem;
        reg valid_to_ext;
        
        localparam IDLE=2'b00,
                   WAIT=2'b01,
                   READ=2'b11;
        reg [1:0] cState,nState;        
        
  
        
    always@(posedge clk_a,negedge arstz_aq)
    begin
    if(!arstz_aq)
    cState <= IDLE;
    else
    cState <= nState;
    end
    
    always@(*)
    begin
    nState = cState;
    case(cState)
    IDLE:begin
        if(en == 1'b1 && we == 1'b0) begin
        if(READ_LATENCY == 1)nState = READ;
	    else nState = WAIT;
        end
    end
    WAIT:begin
        if(wait_counter == READ_LATENCY-1) nState = READ;
        end
    READ:begin
    nState = IDLE;
    end  
    default:begin
    nState=2'bxx;
    end
    endcase
    end
   
    always@(posedge clk_a,negedge arstz_aq)			
    begin
    if(arstz_aq == 1'b0) wait_counter <=0;
    else wait_counter <= wait_counter_next;
    end
    
    always@(*) begin
    wait_counter_next = wait_counter;
    case (cState)
        IDLE: wait_counter_next = 2'b1;
        WAIT: wait_counter_next = wait_counter + 1'b1;
        default: wait_counter_next = 0;
    endcase
    end
  
    always@(*) begin
    en_to_blkmem = en;
    valid_to_ext = 0;
    case(cState)
    IDLE: begin
    en_to_blkmem = en;
    valid_to_ext = 0;
    end
    WAIT: begin
    en_to_blkmem = 1;
    valid_to_ext = 0;
    end
    READ: begin
    en_to_blkmem = 0;
    valid_to_ext = 1;
    end
    endcase
    end
    
  
   /* assign valid = (cState==READ)?1:0;
    assign en = (cState==WAIT||we==1)?1:0;
   */
    assign valid = valid_to_ext;

    
    blk_mem_gen_0 your_instance_name (
    .clka(clk_a),    // input wire clka
    .ena(en_to_blkmem),      // input wire ena
    .wea(we),      // input wire [0 : 0] wea
    .addra(addr),  // input wire [7 : 0] addra
    .dina(din),    // input wire [31 : 0] dina
    .douta(dout)  // output wire [31 : 0] douta
    );    

endmodule