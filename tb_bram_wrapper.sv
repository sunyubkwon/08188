`timescale 1ns / 1ps

module tb_wrapper;

    reg clk_a;
    reg arstz_aq;
    reg en;
    reg we;
    reg [14:0] addr;
    reg  [30:0] din;
    wire [30:0] dout;
    wire valid;

       wrapper #(.READ_LATENCY(3) ) i_bram(
      .clk_a(clk_a),
      .arstz_aq(arstz_aq),
      .addr(addr),
      .en(en),
      .we(we),
      .din(din),
      .dout(dout),
      .valid(valid)
    );
    
    always #5 clk_a=~clk_a;
    initial
    begin
    clk_a=0;
    arstz_aq=0;
    en=0;
    we=0;
    addr=0;
    din=0;
    @(posedge clk_a);
    #1 arstz_aq=1;
    @(posedge clk_a);
    #1 addr=10;din=12;
    @(posedge clk_a);
    #1 en=1;we=1;
    @(posedge clk_a);
    #1 en=0;we=0;
    @(posedge clk_a);
    
    #1 en=1;we=0;
    @(posedge clk_a);
    
    #1 en=0;we=0;
    @(posedge clk_a);
    @(posedge clk_a);
    @(posedge clk_a);
    @(posedge clk_a);
    @(posedge clk_a);
    @(posedge clk_a);
    $finish;
    end
    endmodule
    // clock and reset from domain a
  /*  reg clk_a;
    initial begin clk_a = 0; forever begin #10; clk_a = ~clk_a; end end
    bit arstz_aq;

    task dut_reset_aq();
        #10 arstz_aq <= 0;
        #20 arstz_aq <= 1;
    endtask

    reg  [3:0]  addr;
    reg         en;
    reg         we;
    reg  [15:0] din;
    wire [15:0] dout;
    wire        valid;

    task bram_write;
        input [3:0] task_addr;
        input [15:0] task_din;
        begin
            @(posedge clk_a);
            #10
            addr = task_addr;
            en = 1;
            we = 1;
            din = task_din;

            @(posedge clk_a);
            #10
            addr <= 4'h0;
            en <= 0;
            we <= 0;
            din <= 16'h0;
        end
    endtask

    task bram_read;
        input [3:0] task_addr;
        begin
            @(posedge clk_a);
            #10
            addr = task_addr;
            en = 1;
            we = 0;

            @(posedge clk_a);
            #10
            addr = 4'h0;
            en = 0;
            we = 0;
        end
    endtask

    initial begin
        addr = 4'h0;
        en = 0;
        we = 0;
        din = 16'h0;

        dut_reset_aq();

        // test logics
        #100 bram_write(4'h1, 1);
        #100 bram_write(4'h2, 2);
        #100 bram_read(4'h1);
        // check data_captured and written data
        #100 bram_read(4'h2);
        // check data_captured and written data

     end

       wrapper #(.READ_LATENCY(1) ) i_bram(
      .clk_a(clk_a),
      .arstz_aq(arstz_aq),
      .addr(addr),
      .en(en),
      .we(we),
      .din(din),
      .dout(dout),
      .valid(valid)
    );

    wire [15:0] data_captured;
    data_capture i_data_capture(
        .clk_a(clk_a),
        .arstz_aq(arstz_aq),
        .data_in(dout),
        .valid(valid),
        .data_out(data_captured)
    );

endmodule
*/