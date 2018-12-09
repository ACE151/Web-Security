 	import java.security.*;
    import java.io.*;
    import java.security.cert.*;
    import java.security.cert.Certificate;
public class getX509 {
	
	public static void main(String[] args) throws IOException {
		CertificateFactory cf;
		try {
			 // ��ȡ����ʵ��
			cf = CertificateFactory.getInstance("X.509");
            // ���ļ�������֤��
			FileInputStream in=new FileInputStream("out.cer");
			// ����֤��
		    Certificate c=cf.generateCertificate(in);
		    X509Certificate t=(X509Certificate)c;
		    in.close();
		    String s=c.toString();
		    System.out.println("���֤����Ϣ:\n"+s);
		    System.out.println();
		    System.out.println();
		    System.out.println("�汾��:"+t.getVersion());
		    System.out.println("���к�:"+t.getSerialNumber().toString(16));
		    System.out.println("ǩ���ߣ�"+t.getIssuerDN());
		    System.out.println("��Ч��ʼ���ڣ�"+t.getNotBefore());
		    System.out.println("��Ч��ֹ���ڣ�"+t.getNotAfter());
		    System.out.println("��������"+t.getSubjectDN());
		    System.out.println("ǩ���㷨��"+t.getSigAlgName());
		    System.out.println("ǩ����"+t.getSignature().toString());
		    PublicKey pk=t.getPublicKey();
		    byte [] pkenc=pk.getEncoded();  
		    System.out.println("��Կ:");
		    for(int i=0;i<pkenc.length;i++)System.out.print(pkenc[i]+",");
		    
		    System.out.println();
		} catch (CertificateException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
