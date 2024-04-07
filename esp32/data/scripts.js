$(() => {
    const load_settings = () => {
        $.ajax({
            url: '/get_settings',
            type: 'GET',
            async: false,
            success: (res) => {
                $('#spd-coef').val(res.spd_coef)
                $('#spd-fast').val(res.spd_fast)
                $('#spd-fwd').val(res.spd_fwd)
                $('#spd-back').val(res.spd_back)
                $('#acc-fwd').val(res.acc_fwd)
                $('#acc-back').val(res.acc_back)
                $('#acc-slwdn').val(res.acc_slwdn)
            }});
        };
        load_settings();
    $("#save-btn").click(() => {
        const new_settings = {
            spd_coef : $('#spd-coef').val(),
            spd_fast : $('#spd-fast').val(),
            spd_fwd : $('#spd-fwd').val(),
            spd_back : $('#spd-back').val(),
            acc_fwd : $('#acc-fwd').val(),
            acc_back : $('#acc-back').val(),
            acc_slwdn : $('#acc-slwdn').val(),
        }
        $.ajax({
            url: '/save_settings',
            type: 'POST',
            data: new_settings,
            // contentType: 'application/json; charset=utf-8',
            // dataType: 'json',
            async: false,
            success: (res) => {
                $("#error-container").css("display", "none");
                $("#success").css("display", "block");
                load_settings();
            },
            error: (err) => {
                $("#error-container").css("display", "block");
                $("#success").css("display", "none");
                $("#result-error").text(err.statusText);
                load_settings();
            }
        });
    });
    // Add your code here
});