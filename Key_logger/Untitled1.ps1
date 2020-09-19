Param([string]$Att,[String]$Subj,[String]$Body)
Function Send-EMail
{
    Param(
            [Parameter(`
            Mandatory=$true)]
         [String]$To,
            [Parameter(`
            Mandatory=$true)]
         [STring]$From,
            [Parameter(`
            Mandatory=$true)]
         [String]$Password,
            [Parameter(`
            Mandatory=$true)]
         [String]$Subject,
            [Parameter(`
            Mandatory=$true)]
         [String]$Body,
            [Parameter(`
            Mandatory=$true)]
         [String]$Attachment
        )
    try
    {
        $Msg=New-Object System.Net.Mail.MailMessage($From,$To,$Subject,$Body)
        $Srv="smtp.gmail.com"
        if($Attachment -ne $null)
        {
            try
            {
                $Attachments=$Attachment -split("\:\:");
                ForEach($val in $Attachments)
                {
                    $Attch=New-Object System.Net.Mail.Attachment($val)
                    $Msg.Attachments.Add($Attch)
                }
            }
            catch
            {
                exit 2;
            }
            $client=New-Object Net.Mail.SmtpClient($Srv,587)
            $Client.EnableSsl=$true
            $Client.Credentials=New-Object System.Net.NetworkCredential($From.Split("@")[0],$Password);
            $Client.Send($Msg)
            Remove-Variable -Name Client
            Remove-Variable -Name Password
            exit 7;
        }
    }
    catch
    {
        exit 3;
    }
}

try
{
    Send-Email
        -Attacment $Att
        -To "Address of the recipient"
        -Body $Body
        -Subject $Subj
        -Password "maqahad"
        -From "Address of the sender"
}
catch
{
    exit 4;
}
